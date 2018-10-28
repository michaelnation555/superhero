// Fill out your copyright notice in the Description page of Project Settings.

#include "SHActorSpawner.h"
#include "SHCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/AIModule/Classes/AIController.h"

// Sets default values
ASHActorSpawner::ASHActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereComp;

	SpawnPercentChance = 100;
}

// Called when the game starts or when spawned
void ASHActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (FMath::RandRange(0, 100) > SpawnPercentChance)
		Destroy();
	
	for (int i = 0; i < SpawningActors.Num(); i++)
	{
		SpawnedActors.Add(NULL);
	}
}

// Called every frame
void ASHActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Detects collision when character overlaps the sphere component
void ASHActorSpawner::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ASHCharacter* Character = Cast<ASHCharacter>(OtherActor);
	if (Character)
	{
		APlayerController* playerController = Cast<APlayerController>(Character->GetController());
		if (playerController)
		{
			for (int i = 0; i < SpawningActors.Num() && i < SpawnedActors.Num(); i++)
			{
				FRotator Rotation;
				Rotation.Roll = 0;
				Rotation.Yaw = FMath::RandRange(0, 360);
				Rotation.Pitch = 0;
				SpawnedActors[i] = GetWorld()->SpawnActor<AActor>(SpawningActors[i].SpawningActor, GetActorLocation() + SpawningActors[i].SpawnOffset, Rotation);
			}
		}
	}
}

// Detects collision when character overlaps the sphere component
void ASHActorSpawner::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ASHCharacter* Character = Cast<ASHCharacter>(OtherActor);
	if (Character)
	{
		APlayerController* playerController = Cast<APlayerController>(Character->GetController());
		if (playerController)
		{
			for (int i = 0; i < SpawnedActors.Num(); i++)
			{
				if (SpawnedActors[i] != NULL)
				{
					/*APawn* Pawn = Cast<APawn>(SpawnedActors[i]);
					if (Pawn != NULL)
					{
						Pawn->Controller->UnPossess();
						Pawn->Controller->Destroy();
						FString Message = "UnPossess";
						GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, Message);
					}*/
					SpawnedActors[i]->Destroy();
				}
			}
		}
	}
}
