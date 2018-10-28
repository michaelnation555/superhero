// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHBuildingGenerator.h"
#include "SHParkGenerator.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHParkGenerator : public ASHBuildingGenerator
{
	GENERATED_BODY()

public:

	// Every park has one pathway to walk through
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Pathway;

	// Other blocks will all be trees
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Trees;

	// Spawn the office building
	virtual void SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks) override;
};
