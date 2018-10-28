// Fill out your copyright notice in the Description page of Project Settings.

#include "SHOfficeGenerator.h"

// Spawn the office building
void ASHOfficeGenerator::SpawnBuilding(int Width, int Height, float DistanceBetweenBlocks)
{
	//FString Message = "Office Building";
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, Message);

	/*FString DebugMessage = "Office Building: ";
	DebugMessage += " (";
	DebugMessage += FString::FromInt(Width);
	DebugMessage += ", ";
	DebugMessage += FString::FromInt(Height);
	DebugMessage += ")";
	DebugMessage += FString::SanitizeFloat(DistanceBetweenBlocks);
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, DebugMessage);*/

	if (MinFloors <= 0 || MaxFloors <= 0 || MinFloors > MaxFloors)
		return;

	// Get random number of Floors
	Floors = MinFloors + (rand() % (int)(MaxFloors - MinFloors + 1));

	for (int f = 0; f <= Floors; ++f)
	{
		for (int w = 0; w < Width; ++w)
		{
			for (int h = 0; h < Height; ++h)
			{
				FVector Location = GetActorLocation();
				Location.X += w * DistanceBetweenBlocks;
				Location.Y += -h * DistanceBetweenBlocks;
				Location.Z += f * DistanceBetweenBlocks / 4;

				if (f == Floors) // Roof
				{
					// Spawn Roof
					GetWorld()->SpawnActor<AActor>(Roof, Location, FRotator::ZeroRotator);
				}

				else
				{
					if (f == 0) // First Floor
					{
						// Spawn Floors
						GetWorld()->SpawnActor<AActor>(Floor, Location, FRotator::ZeroRotator);

						// Spawn West Entrances
						if (w == 0)
							GetWorld()->SpawnActor<AActor>(Entrance, Location, FRotator(0, 90, 0));
						// Spawn East Windows
						if (w == Width - 1)
							GetWorld()->SpawnActor<AActor>(Entrance, Location, FRotator(0, 270, 0));
						// Spawn South Windows
						if (h == 0)
							GetWorld()->SpawnActor<AActor>(Entrance, Location, FRotator(0, 0, 0));
						// Spawn North Windows
						if (h == Height - 1)
							GetWorld()->SpawnActor<AActor>(Entrance, Location, FRotator(0, 180, 0));
					}

					else // Floors above First Floor
					{
						// Spawn Floors with Stairwells
						GetWorld()->SpawnActor<AActor>(Stairs, Location, FRotator::ZeroRotator);

						// Spawn West Windows
						if (w == 0)
							GetWorld()->SpawnActor<AActor>(Window, Location, FRotator(0, 90, 0));
						// Spawn East Windows
						if (w == Width - 1)
							GetWorld()->SpawnActor<AActor>(Window, Location, FRotator(0, 270, 0));
						// Spawn South Windows
						if (h == 0)
							GetWorld()->SpawnActor<AActor>(Window, Location, FRotator(0, 0, 0));
						// Spawn North Windows
						if (h == Height - 1)
							GetWorld()->SpawnActor<AActor>(Window, Location, FRotator(0, 180, 0));
					}
				}
			}
		}
	}
	Destroy(); // Destroy self after building has been generated
}
