// Fill out your copyright notice in the Description page of Project Settings.

#include "SHCostumeComponent.h"

// Sets default values for this component's properties
USHCostumeComponent::USHCostumeComponent()
{
	CurrentHeadgearIndex = 0;
}

// Called when the game starts
void USHCostumeComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->GetComponents<USkeletalMeshComponent>(SkeletalMeshComps);
	if (SkeletalMeshComps[0] != nullptr)
	{
		HeadgearMeshComp = Cast<UStaticMeshComponent>(SkeletalMeshComps[0]->GetChildComponent(0));
	}
	//SkeletalMeshComps[0]->GetComponents<UStaticMeshComponent>(HeadgearMeshComps);
	//GetOwner()->GetComponents<UStaticMeshComponent>(HeadgearMeshComps);

	// Apply default color scheme
	if (ColorSchemes.Num() > 0)
		ApplyColorSchemeByIndex(0);
}

// Set the character's headgear
void USHCostumeComponent::SetHeadgear(int Index)
{
	//FString Message = "Change headgear 1";
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, Message);

	if (Index >= Headgears.Num() || HeadgearMeshComp == nullptr)
		return;
	CurrentHeadgearIndex = Index;
	HeadgearMeshComp->SetStaticMesh(Headgears[Index]);
}

// Apply the next Headgear in the list, 1 for next, -1 for previous
void USHCostumeComponent::ApplyNextHeadgear(int Offset)
{
	CurrentHeadgearIndex += Offset;
	if (CurrentHeadgearIndex >= Headgears.Num())
		CurrentHeadgearIndex = 0;
	else if (CurrentHeadgearIndex < 0)
		CurrentHeadgearIndex = Headgears.Num() - 1;
	SetHeadgear(CurrentHeadgearIndex);
}

// Apply a specific color to current headgear
void USHCostumeComponent::ApplyHeadgearColor(int ColorIndex, int MeshIndex)
{
	if (Colors[ColorIndex] == nullptr || HeadgearMeshComp == nullptr)
		return;
	HeadgearMeshComp->SetMaterial(MeshIndex, Colors[ColorIndex]);
}

// Apply a specific color to a specific part of the character model
void USHCostumeComponent::ApplyColor(int ColorIndex, int MeshIndex)
{
	if (SkeletalMeshComps[0] == nullptr)
		return;
	SkeletalMeshComps[0]->SetMaterial(MeshIndex, Colors[ColorIndex]);
}

// Change a character model's color scheme and apply the colors
void USHCostumeComponent::ApplyColorScheme(FColorScheme ColorScheme)
{
	CurrentColorScheme = ColorScheme;

	// For each color group i.e. Skin, Primary, Secondary...
	for (int i = 0; i < CurrentColorScheme.Groups.Num(); ++i)
	{
		// For each slot in the color group i.e. 0, 1... where 0 = feet, 1 = shins
		for (int j = 0; j < CurrentColorScheme.Groups[i].Slots.Num(); ++j)
		{
			//if (CurrentColors[i])
			ApplyColor(CurrentColors[i], CurrentColorScheme.Groups[i].Slots[j]);
		}
	}
}

// Change a character model's color scheme by index
void USHCostumeComponent::ApplyColorSchemeByIndex(int Index)
{
	CurrentColorSchemeIndex = Index;
	ApplyColorScheme(ColorSchemes[Index]);
}

// Apply the next Color Scheme in the list, 1 for next, -1 for previous
void USHCostumeComponent::ApplyNextColorSchemeByOffset(int Offset)
{
	CurrentColorSchemeIndex += Offset;

	if (CurrentColorSchemeIndex >= ColorSchemes.Num())
		CurrentColorSchemeIndex = 0;
	else if (CurrentColorSchemeIndex < 0)
		CurrentColorSchemeIndex = ColorSchemes.Num() - 1;

	ApplyColorScheme(ColorSchemes[CurrentColorSchemeIndex]);
}
