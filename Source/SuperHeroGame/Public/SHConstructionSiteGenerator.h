// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHBuildingGenerator.h"
#include "SHConstructionSiteGenerator.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHConstructionSiteGenerator : public ASHBuildingGenerator
{
	GENERATED_BODY()

public:

	// Every construction site will have exactly one crane
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TSubclassOf<AActor> Crane;

	// Other possible blocks to be spawned in the construction site
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Building)
	TArray<TSubclassOf<AActor>> Blocks;

	// Spawn the construction site
	virtual void SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks) override;
};
