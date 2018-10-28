// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHBuildingGenerator.h"
#include "SHOfficeGenerator.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHEROGAME_API ASHOfficeGenerator : public ASHBuildingGenerator
{
	GENERATED_BODY()

public:

	// The number of floors in the office building
	UPROPERTY(BlueprintReadOnly, Category = Building)
	int Floors;

	// The minimum number of floors in the office building
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	int MinFloors;

	// The maximum number of floors in the office building
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	int MaxFloors;

	//--Office building assets-------------------------------------//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Floor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Window;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Roof;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Entrance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Stairs;
	//-------------------------------------------------------------//
	
	// Spawn the office building
	virtual void SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks) override;

};
