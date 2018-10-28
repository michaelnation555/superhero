// Fill out your copyright notice in the Description page of Project Settings.

#include "SHParkGenerator.h"

// Spawn the park
void ASHParkGenerator::SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks)
{
	int wIndex = FMath::RandRange(0, Width - 1); // Where to spawn pathways
	int Rotations[4] = { 0, 90, 180, 270 };
	for (int w = 0; w < Width; ++w)
	{
		for (int h = 0; h < Height; ++h)
		{
			FVector Location = GetActorLocation();
			Location.X += w * DistanceBetweenBlocks;
			Location.Y += -h * DistanceBetweenBlocks;
			Location.Z = 0;
			if (w == wIndex && Pathway != NULL)
			{
				GetWorld()->SpawnActor<AActor>(Pathway, Location, FRotator::ZeroRotator);
			}
			else if (Trees != NULL)
			{
				FRotator Rotation;
				Rotation.Roll = 0;
				Rotation.Yaw = Rotations[FMath::RandRange(0, 3)];
				Rotation.Pitch = 0;
				GetWorld()->SpawnActor<AActor>(Trees, Location, Rotation);
			}
		}
	}

	Destroy(); // Destroy self after building has been generated
}