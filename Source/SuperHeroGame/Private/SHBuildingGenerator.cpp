// Fill out your copyright notice in the Description page of Project Settings.

#include "SHBuildingGenerator.h"

// Sets default values
ASHBuildingGenerator::ASHBuildingGenerator()
{

}

// Called when the game starts or when spawned
void ASHBuildingGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Spawn the building
void ASHBuildingGenerator::SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks)
{
	FString Message = "Default Building";
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, Message);

	/*FString DebugMessage = "Building Area: ";
	DebugMessage += " (";
	DebugMessage += FString::FromInt(Width);
	DebugMessage += ", ";
	DebugMessage += FString::FromInt(Height);
	DebugMessage += ")";
	DebugMessage += FString::SanitizeFloat(DistanceBetweenBlocks);
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, DebugMessage);*/

	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			FVector Location = GetActorLocation();
			Location.X += i * DistanceBetweenBlocks;
			Location.Y += -j * DistanceBetweenBlocks;
			GetWorld()->SpawnActor<AActor>(Building, Location, FRotator::ZeroRotator);
		}
	}
}
