// Fill out your copyright notice in the Description page of Project Settings.

#include "SHCityGenerator.h"
#include "SHBuildingGenerator.h"

// Sets default values
ASHCityGenerator::ASHCityGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASHCityGenerator::BeginPlay()
{
	Super::BeginPlay();

	// Create the MapGrid with default values
	for (int i = 0; i < Width; ++i)
	{
		MapGrid.AddNewColumn();
		for (int j = 0; j < Height; ++j)
		{
			MapGrid.Columns[i].AddNewRow();
		}
	}

	// Setup vertical and horizontal roads
	SetupRoads();

	// Setup building
	SetupBuildings();

	// Spawn the 3D assets according to the MapGrid
	SpawnRoads();

	// Spawn the building generators that will generate buildings
	SpawnBuildingGenerators();

	// Print the MapGrid to the screen
	//MapGrid.Print();

	// Destroy self after city has been generated
	Destroy();
}

// Called every frame
void ASHCityGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set rows and columns for roads in the MapGrid
// Mapgrid:
// 0  = Default
// 1 = Vertical Road
// 2 = Horizontal Road
// 3 = Intersection Road
// 4 = Building
void ASHCityGenerator::SetupRoads()
{
	if (MinBlocksBetweenRoads <= 0 || MaxBlocksBetweenRoads <= 0 || MinBlocksBetweenRoads > MaxBlocksBetweenRoads)
		return;

	// Setup vertical roads
	for (int i = 0; i < Width; i += MinBlocksBetweenRoads + (rand() % (int)(MaxBlocksBetweenRoads - MinBlocksBetweenRoads + 1)))
	{
		for (int j = 0; j < Height; ++j)
		{
			MapGrid.Columns[i].Rows[j] += 1;
		}
	}

	// Setup horizontal roads
	for (int j = 0; j < Height; j += MinBlocksBetweenRoads + (rand() % (int)(MaxBlocksBetweenRoads - MinBlocksBetweenRoads + 1)))
	{
		for (int i = 0; i < Width; ++i)
		{
			MapGrid.Columns[i].Rows[j] += 2;
		}
	}
}

// Setup building areas
// Mapgrid:
// 0  = Default
// 1 = Vertical Road
// 2 = Horizontal Road
// 3 = Intersection Road
// 4 = Building
void ASHCityGenerator::SetupBuildings()
{
	int w = 0;
	int h = 0;
	int count = 0;

	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			FBuildingArea buildingArea;
			buildingArea.X = 0;
			buildingArea.Y = 0;
			buildingArea.Width = 0;
			buildingArea.Height = 0;

			if (MapGrid.Columns[i].Rows[j] == 0) // Found building area position
			{
				// Find Width
				w = 0;
				for (int x = i; x < Width && MapGrid.Columns[x].Rows[j] == 0; ++x)
				{
					++w;
				}

				// Find Height
				h = 0;
				for (int y = j; y < Height && MapGrid.Columns[i].Rows[y] == 0; ++y)
				{
					++h;
				}

				// Set values to 4
				for (int x = 0; x < w; ++x)
				{
					for (int y = 0; y < h; ++y)
					{
						MapGrid.Columns[i + x].Rows[j + y] = 4;
					}
				}

				buildingArea.X = i;
				buildingArea.Y = j;
				buildingArea.Width = w;
				buildingArea.Height = h;
				BuildingAreas.Add(buildingArea);

				/*FString DebugMessage = "Building Area: ";
				DebugMessage += FString::FromInt(count);
				DebugMessage += " (";
				DebugMessage += FString::FromInt(i);
				DebugMessage += ", ";
				DebugMessage += FString::FromInt(j);
				DebugMessage += ") Width: ";
				DebugMessage += FString::FromInt(w);
				DebugMessage += ", Height: ";
				DebugMessage += FString::FromInt(h);
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, DebugMessage);
				++count;*/
			}
		}
	}
}

// Spawn the 3D assets according to the MapGrid
void ASHCityGenerator::SpawnRoads()
{
	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			if (MapGrid.Columns[i].Rows[j] == 0)
				GetWorld()->SpawnActor<AActor>(DefaultBlock, FVector(i * DistanceBetweenBlocks, -j * DistanceBetweenBlocks,0), FRotator::ZeroRotator);
			else if (MapGrid.Columns[i].Rows[j] == 1)
				GetWorld()->SpawnActor<AActor>(Road, FVector(i * DistanceBetweenBlocks, -j * DistanceBetweenBlocks, 0), FRotator(0, 90, 0));
			else if (MapGrid.Columns[i].Rows[j] == 2)
				GetWorld()->SpawnActor<AActor>(Road, FVector(i * DistanceBetweenBlocks, -j * DistanceBetweenBlocks, 0), FRotator::ZeroRotator);
			else if (MapGrid.Columns[i].Rows[j] == 3)
				GetWorld()->SpawnActor<AActor>(IntersectionRoad, FVector(i * DistanceBetweenBlocks, -j * DistanceBetweenBlocks, 0), FRotator::ZeroRotator);
		}
	}
}

// Spawn the building generators that will generate buildings
void ASHCityGenerator::SpawnBuildingGenerators()
{
	int index = 0;
	for (int i = 0; i < BuildingAreas.Num(); ++i)
	{
		index = FMath::RandRange(0, BuildingGenerators.Num() - 1);
		if (BuildingGenerators[index] != NULL)
		{
			ASHBuildingGenerator* buildingGenerator = (ASHBuildingGenerator*)GetWorld()->SpawnActor<AActor>(BuildingGenerators[index], FVector(BuildingAreas[i].X * DistanceBetweenBlocks, -BuildingAreas[i].Y * DistanceBetweenBlocks, 0), FRotator::ZeroRotator);
			buildingGenerator->SpawnBuilding(BuildingAreas[i].Width, BuildingAreas[i].Height, DistanceBetweenBlocks);
		}
	}
}
