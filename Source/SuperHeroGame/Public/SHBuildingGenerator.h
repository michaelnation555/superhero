// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SHBuildingGenerator.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHBuildingGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASHBuildingGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Building;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Spawn the building
	virtual void SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks);

};
