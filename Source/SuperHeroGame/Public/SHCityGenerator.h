// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SHCityGenerator.generated.h"

USTRUCT()
struct FBuildingArea // Each FBuildingArea is an entire city block which will be used to spawn groups of buildings
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		int X;
		UPROPERTY()
		int Y;
		UPROPERTY()
		int Width;
		UPROPERTY()
		int Height;

		FBuildingArea()
		{
			X = 0;
			Y = 0;
			Width = 0;
			Height = 0;
		}
};

USTRUCT()
struct FMapGridColumn // Each FMapGrid consists of FMapGridRows, and each FMapGridRows consists of Columns
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<int> Rows;

	void AddNewRow()
	{
		Rows.Add(0); // 0 = Default, 1 = Horizontal, 2 = Vertical, 3 = Intersection
	}
};

USTRUCT()
struct FMapGrid // The Mapgrid calculated before placing each city block into the map
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<FMapGridColumn> Columns;

	void AddNewColumn()
	{
		Columns.Add(FMapGridColumn());
	}

	void Print()
	{
		if (GEngine)
		{
			FString DebugMessage = "";
			for (int j = Columns[0].Rows.Num() - 1; j >= 0 ; --j) // Assuming all Rows are same length
			{
				for (int i = 0; i < Columns.Num(); ++i)
				{
					DebugMessage += FString::FromInt(Columns[i].Rows[j]) + " ";
				}
				DebugMessage += "\n";
			}
			FString MapGrid = FString::Printf(TEXT("%s"), *DebugMessage);
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, MapGrid);
		}
	}
};

UCLASS()
class SUPERHEROGAME_API ASHCityGenerator : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASHCityGenerator();

	// The matrix represting the types of blocks to spawn in the city
	FMapGrid MapGrid;

	// The list of all building areas in the city which will contain groups of buildings
	TArray<FBuildingArea> BuildingAreas;

	// The width of the entire city
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	int Width;

	// The height of the entire city
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	int Height;

	// The minimum distance in blocks between each road
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	int MinBlocksBetweenRoads;

	// The maximum distance in blocks between each road
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	int MaxBlocksBetweenRoads;

	// The distance between each block
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	float DistanceBetweenBlocks;

	//--City block assets--------------------------------------//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	TSubclassOf<AActor> DefaultBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	TSubclassOf<AActor> Road;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	TSubclassOf<AActor> IntersectionRoad;
	//---------------------------------------------------------//

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	TArray<TSubclassOf<AActor>> BuildingGenerators;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Set rows and columns for roads in the MapGrid
	void SetupRoads();

	// Setup building
	void SetupBuildings();

	// Spawn the 3D assets according to the MapGrid
	void SpawnRoads();

	// Spawn the building generators that will generate buildings
	void SpawnBuildingGenerators();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
