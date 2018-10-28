// Fill out your copyright notice in the Description page of Project Settings.

#include "SHCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASHCharacter::ASHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 98.0f);

	// Set our turn rates for input
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Set default values for melee
	MaxMeleeWalkSpeed = 1000.0f;

	// Set default values for aiming
	Aiming = false;
	AimRotationSpeed = 0.1f;
	MaxAimingWalkSpeed = 250.0f;

	// Set default values for sprinting
	MaxSprintSpeed = 2000.0f;
	Sprinting = false;
	SprintEnergyConsumptionRate = 20.0f;

	// Set default values for flying
	//MaxSoarSpeed = 2000.0f;
	FlyEnergyConsumptionRate = 10.0f;

	// Set default values for jumping
	BaseJumpZVelocity = 500.0f;
	MaxJumpCharge = 2000.0f;
	CurrentJumpCharge = 0.0f;
	JumpChargeRate = 2000.0f;
	ChargingJump = false;
	ChargedJumpEnergyConsumptionRate = 50.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FVector(-100, 0, 50));
	DefaultCameraLocation = FollowCamera->GetRelativeTransform().GetLocation();
	AimingCameraLocation = FVector(100, 80, 80);
	InventoryCameraLocation = FVector(0, -200, 0);
}

// Called when the game starts or when spawned
void ASHCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set default target camera relative location
	TargetCameraLocation = DefaultCameraLocation;

	// Set default speeds
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	DefaultFlySpeed = GetCharacterMovement()->MaxFlySpeed;

	// Set Energy Component
	EnergyComponent = FindComponentByClass<USHEnergyComponent>();

	// Set Inventory Component
	InventoryComponent = FindComponentByClass<USHInventoryComponent>();
}

// Called every frame
void ASHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Charge up jump strength while player holding jump button
	if (ChargingJump && CurrentJumpCharge < MaxJumpCharge && EnergyComponent->CurrentEnergy > 0)
	{
		CurrentJumpCharge = CurrentJumpCharge + (GetWorld()->GetDeltaSeconds() * JumpChargeRate);
		EnergyComponent->Consume(GetWorld()->GetDeltaSeconds() * ChargedJumpEnergyConsumptionRate);
	}
	// Cap the jump charge to the maximum jump charge possible
	if (CurrentJumpCharge > MaxJumpCharge)
		CurrentJumpCharge = MaxJumpCharge;

	// When flying check if the ground is under the character
	if (CheckGroundBelow())
		EndFly();

	// When flying speed drops below 50% of MaxDefaultFlySpeed stop soaring
	//if (Soaring && GetVelocity().Size() < 0.5f * DefaultFlySpeed)
		//EndSoar();

	// Consume energy while flying
	if (GetCharacterMovement()->MovementMode == MOVE_Flying)
		EnergyComponent->Consume(GetWorld()->GetDeltaSeconds() * FlyEnergyConsumptionRate);

	// Consume energy while sprinting
	if (Sprinting)
		EnergyComponent->Consume(GetWorld()->GetDeltaSeconds() * SprintEnergyConsumptionRate);

	// Out of energy
	if (EnergyComponent->CurrentEnergy <= 0)
	{
		if (Sprinting)
			EndSprint();
		if (GetCharacterMovement()->MovementMode == MOVE_Flying)
			EndFly();
	}

	// Rotate character while aiming
	if (Aiming)
	{
		FRotator Rotation = GetControlRotation();
		Rotation.Pitch = 0;
		Rotation.Roll = 0;
		SetActorRotation(FMath::Lerp(GetActorRotation(), Rotation, AimRotationSpeed));
	}

	// Set camera to aiming position
	FollowCamera->SetRelativeLocation(FMath::VInterpTo(FollowCamera->GetRelativeTransform().GetLocation(), TargetCameraLocation, 0.5f, 0.05f));

	// Move forward while melee attacking
	if (MeleeMoving && !GetCharacterMovement()->IsFalling() && !GetCharacterMovement()->IsFlying())
	{
		if ((Controller != NULL))
		{
			// get forward vector
			const FVector Direction = GetActorForwardVector();
			AddMovementInput(Direction, 1);
		}
	}
}

void ASHCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && (!MeleeAttacking || GetCharacterMovement()->IsFalling() || GetCharacterMovement()->IsFlying()))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();

		float Pitch = 0;
		float Yaw = Rotation.Yaw;
		float Roll = 0;

		// if flying, account for pitch and roll rotation when moving
		if (GetCharacterMovement()->IsFlying())
		{
			Pitch = Rotation.Pitch;
			Roll = Rotation.Roll;
		}

		const FRotator YawRotation(Pitch, Yaw, Roll);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASHCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && (!MeleeAttacking || GetCharacterMovement()->IsFalling() || GetCharacterMovement()->IsFlying()))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASHCharacter::MoveUp(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get up vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASHCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASHCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASHCharacter::StartAim()
{
	Aiming = true;
	Sprinting = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	TargetCameraLocation = AimingCameraLocation;
	GetCharacterMovement()->MaxWalkSpeed = MaxAimingWalkSpeed;
}

void ASHCharacter::EndAim()
{
	Aiming = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	TargetCameraLocation = DefaultCameraLocation;
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void ASHCharacter::StartSprint()
{
	if (EnergyComponent->CurrentEnergy > 0 && GetCharacterMovement()->MovementMode == MOVE_Walking && !Aiming)
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
		Sprinting = true;
	}
}

void ASHCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	Sprinting = false;
}

/*void ASHCharacter::StartSoar()
{
	// Can only start soaring if current speed is at least 50% of MaxDefaultFlySpeed
	if (GetCharacterMovement()->MovementMode == MOVE_Flying && GetVelocity().Size() > 0.5f * DefaultFlySpeed)
	{
		Soaring = true;
		GetCharacterMovement()->MaxFlySpeed = MaxSoarSpeed;
		//GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}*/

/*void ASHCharacter::EndSoar()
{
	Soaring = false;
	GetCharacterMovement()->MaxFlySpeed = DefaultFlySpeed;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
}*/

void ASHCharacter::ChargeUpJump()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Walking && !MeleeAttacking)
	{
		if (MaxJumpCharge == 0.0f)
		{
			Jump();
			return;
		}
		CurrentJumpCharge = 0.0f;
		ChargingJump = true;
		UGameplayStatics::PlaySoundAtLocation(this, ChargeJumpSound, GetActorLocation());
	}
}

void ASHCharacter::ChargedJump()
{
	if (MaxJumpCharge == 0.0f || MeleeAttacking || GetCharacterMovement()->MovementMode == MOVE_Flying)
		return;
	ChargingJump = false;
	GetCharacterMovement()->JumpZVelocity = BaseJumpZVelocity + CurrentJumpCharge;
	Jump();
	CurrentJumpCharge = 0.0f;
	UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
}

void ASHCharacter::StartFly()
{
	if (GetCharacterMovement()->IsFalling() && EnergyComponent->CurrentEnergy > 0)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		UGameplayStatics::PlaySoundAtLocation(this, StartFlySound, GetActorLocation());
	}
}

void ASHCharacter::EndFly()
{
	//EndSoar();
	if (GetCharacterMovement()->MovementMode == MOVE_Flying)
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

bool ASHCharacter::CheckGroundBelow()
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = GetActorLocation();
	FVector DownwardVector = FVector(0, 0, -1);
	FVector EndTrace = ((DownwardVector * 100.0f) + StartTrace);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true);
		return true;
	}
	return false;
}

// Use the item i.e. attack, shoot, throw etc...
void ASHCharacter::StartUse()
{
	if (InventoryComponent)
	{
		if (InventoryComponent->CurrentItem)
			InventoryComponent->CurrentItem->StartUse();
	}
}

// Stop using the item i.e. stop automatic fire... or stop charging weapon
void ASHCharacter::EndUse()
{
	if (InventoryComponent)
	{
		if (InventoryComponent->CurrentItem)
			InventoryComponent->CurrentItem->EndUse();
	}
}

// Equip an item from a given slot number
void ASHCharacter::EquipItem(int slot)
{
	if (!MeleeAttacking)
		InventoryComponent->EquipItem(slot);
}

template<int slot>
void ASHCharacter::EquipItem()
{
	EquipItem(slot);
}

void ASHCharacter::StartMeleeAttack()
{
	MeleeAttacking = true;
}

void ASHCharacter::EndMeleeAttack()
{
	MeleeAttacking = false;
}

void ASHCharacter::StartMeleeMove()
{
	MeleeMoving = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxMeleeWalkSpeed;
}

void ASHCharacter::EndMeleeMove()
{
	MeleeMoving = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void ASHCharacter::Destroyed()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "FreeRoam");
	}
}

// Called to bind functionality to input
void ASHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ASHCharacter::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ASHCharacter::EndAim);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASHCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASHCharacter::EndSprint);
	//PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASHCharacter::StartSoar);
	//PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASHCharacter::EndSoar);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASHCharacter::ChargeUpJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASHCharacter::ChargedJump);
	PlayerInputComponent->BindAction("Fly", IE_Pressed, this, &ASHCharacter::StartFly);
	PlayerInputComponent->BindAction("Stop Fly", IE_Pressed, this, &ASHCharacter::EndFly);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ASHCharacter::StartUse);
	PlayerInputComponent->BindAction("Use", IE_Released, this, &ASHCharacter::EndUse);
	PlayerInputComponent->BindAction("Equip Item 1", IE_Pressed, this, &ASHCharacter::EquipItem<1>);
	PlayerInputComponent->BindAction("Equip Item 2", IE_Pressed, this, &ASHCharacter::EquipItem<2>);
	PlayerInputComponent->BindAction("Equip Item 3", IE_Pressed, this, &ASHCharacter::EquipItem<3>);
	PlayerInputComponent->BindAction("Equip Item 4", IE_Pressed, this, &ASHCharacter::EquipItem<4>);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASHCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASHCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASHCharacter::MoveUp);
	PlayerInputComponent->BindAxis("Turn", this, &ASHCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASHCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ASHCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASHCharacter::LookUpAtRate);
}