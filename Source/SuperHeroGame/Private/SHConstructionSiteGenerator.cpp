// Fill out your copyright notice in the Description page of Project Settings.

#include "SHConstructionSiteGenerator.h"

// Spawn the construction site
void ASHConstructionSiteGenerator::SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks)
{
	int count = 0; // Keep track of number of blocks spawned
	int CraneCount = FMath::RandRange(0, Width * Height - 1); // Where to spawn the crane
	int RandBlockIndex = 0;
	int Rotations[4] = { 0, 90, 180, 270 };
	for (int w = 0; w < Width; ++w)
		{
		for (int h = 0; h < Height; ++h)
		{
			FVector Location = GetActorLocation();
			Location.X += w * DistanceBetweenBlocks;
			Location.Y += -h * DistanceBetweenBlocks;
			Location.Z = 0;
			FRotator Rotation;
			Rotation.Roll = 0;
			Rotation.Yaw = Rotations[FMath::RandRange(0, 3)];
			Rotation.Pitch = 0;
			RandBlockIndex = FMath::RandRange(0, Blocks.Num() - 1);
			if (count == CraneCount && Crane != NULL) // Spawn the crane
			{
				GetWorld()->SpawnActor<AActor>(Crane, Location, Rotation);
			}
			else if (Blocks[RandBlockIndex] != NULL) // Spawn a random block
			{
				GetWorld()->SpawnActor<AActor>(Blocks[RandBlockIndex], Location, Rotation);
			}
			count++;
		}
	}

	Destroy(); // Destroy self after building has been generated
}