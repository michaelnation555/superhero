// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SHEnergyComponent.h"
#include "SHInventoryComponent.h"
#include "SHCharacter.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// The boom that the camera is attached to
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// The camera that follows the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Sets default values for this character's properties
	ASHCharacter();

	// Base turn rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	// Base look up and down rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// Relative Location of the camera by default
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	FVector DefaultCameraLocation;

	// Relative Location of the camera when aiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	FVector AimingCameraLocation;

	// Relative Location of the camera when using inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	FVector InventoryCameraLocation;

	// Relative Location of where to move the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	FVector TargetCameraLocation;

	// Energy Component for using abilities
	USHEnergyComponent* EnergyComponent;

	// Inventory Component for using items
	USHInventoryComponent* InventoryComponent;

	// True if the character is melee attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Melee)
	bool MeleeAttacking;

	// True if the character is melee moving
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Melee)
	bool MeleeMoving;

	// Max speed while character is melee attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Melee)
	float MaxMeleeWalkSpeed;

	// True if character is aiming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Aiming)
	bool Aiming;

	// Speed of rotating while aiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aiming)
	float AimRotationSpeed;

	// Max speed while character is aiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aiming)
	float MaxAimingWalkSpeed;

	// Max speed while character is sprinting
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sprinting)
	float MaxSprintSpeed;

	// True if character is sprinting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprinting)
	bool Sprinting;

	// Rate of using Energy to sprint
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sprinting)
	float SprintEnergyConsumptionRate;

	// Default walk speed
	float DefaultWalkSpeed;

	// Max speed while character is soaring
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Flying)
	//float MaxSoarSpeed;

	// Default fly speed
	float DefaultFlySpeed;

	// True if the character is currently soaring
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Flying)
	//bool Soaring;

	// True if the character is currently flying upwards
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Flying)
	bool FlyingUp;

	// Rate of using Energy to fly
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Flying)
	float FlyEnergyConsumptionRate;

	// Base character jump strength
	// JumpZVelocity = BaseJumpVelocity + CurrentJumpCharge
	UPROPERTY(EditDefaultsOnly, Category = Jumping)
	float BaseJumpZVelocity;

	// Max jump strength the character can charge up to
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Jumping)
	float MaxJumpCharge;

	// Current jump strength
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Jumping)
	float CurrentJumpCharge;

	// Rate of charging jump
	UPROPERTY(EditDefaultsOnly, Category = Jumping)
	float JumpChargeRate;

	// True if the character is currently charging up jump
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Jumping)
	bool ChargingJump;

	// Rate of using Energy to do a charged jump
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Jumping)
	float ChargedJumpEnergyConsumptionRate;

	// Sound effect played when charging jump
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* ChargeJumpSound;

	// Sound effect played when jumping
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* JumpSound;

	// Sound effect played when start flying
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* StartFlySound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Move forward and back
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	// Move right and left
	void MoveRight(float Value);

	// Move up and down
	void MoveUp(float Value);

	// Turn right and left
	void TurnAtRate(float Rate);

	// Look up and down
	void LookUpAtRate(float Rate);

	// Start aiming
	void StartAim();

	// Stop aiming
	void EndAim();

	// Start sprinting
	void StartSprint();

	// Stop sprinting
	void EndSprint();

	// Start soaring
	//void StartSoar();

	// Stop soaring
	//void EndSoar();

	// Charge up the character jump
	void ChargeUpJump();

	// Jump according to how long the character was charging
	void ChargedJump();

	// Start flying
	void StartFly();

	// Stop flying
	void EndFly();

	// Stop flying if the ground is below the character
	bool CheckGroundBelow();

	// Use the item i.e. attack, shoot, throw etc...
	UFUNCTION(BlueprintCallable, Category = "Item")
	void StartUse();

	// Stop using the item i.e. stop automatic fire... or stop charging weapon
	void EndUse();

	// Equip an item from a given slot number
	void EquipItem(int slot);
	
	// Template version which calls EquipItem
	template<int slot>
	void EquipItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start melee attack
	UFUNCTION(BlueprintCallable, Category = "Melee")
	void StartMeleeAttack();

	// Stop melee attack
	UFUNCTION(BlueprintCallable, Category = "Melee")
	void EndMeleeAttack();

	// Start melee move
	UFUNCTION(BlueprintCallable, Category = "Melee")
	void StartMeleeMove();

	// Stop melee move
	UFUNCTION(BlueprintCallable, Category = "Melee")
	void EndMeleeMove();

	// Update inventory screen with new item icon
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInventoryScreen(int index, UTexture2D* Texture);

	// Called when the actor is destroyed
	virtual void Destroyed();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
