// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SHActorSpawner.generated.h"

USTRUCT(BlueprintType)
struct FSpawningActor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawningActor;
	UPROPERTY(EditAnywhere)
	FVector SpawnOffset;

	FSpawningActor()
	{
		SpawningActor = NULL;
		SpawnOffset = FVector(0, 0, 0);
	}
};

UCLASS()
class SUPERHEROGAME_API ASHActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASHActorSpawner();

	// The sphere component used for detecting collision with character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = pickup)
	USphereComponent* SphereComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Percentage chance of being deleted
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	int32 SpawnPercentChance;

	// List of actors to spawn when character enters sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TArray<FSpawningActor> SpawningActors;

	// List of actors that have been spawned
	TArray<AActor*> SpawnedActors;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Detects collision when character overlaps the sphere component
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Detects collision when character leaves the sphere component
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

};
