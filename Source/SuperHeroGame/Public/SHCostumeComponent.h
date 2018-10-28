// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHCostumeComponent.generated.h"

USTRUCT(BlueprintType)
struct FColorGroups
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> Slots;
};

USTRUCT(BlueprintType)
struct FColorScheme
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColorGroups> Groups;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHEROGAME_API USHCostumeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USHCostumeComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TArray<USkeletalMeshComponent*> SkeletalMeshComps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* HeadgearMeshComp;

	// The index of the current headgear
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Headgear)
	int CurrentHeadgearIndex;

	// List of all available headgear to wear
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Headgear)
	TArray<UStaticMesh*> Headgears;

	// List of all colors available for customization
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<UMaterial*> Colors;

	// List of all colorschemes available for customization
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<FColorScheme> ColorSchemes;

	// The current color scheme the character model is using
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Colors)
	FColorScheme CurrentColorScheme;

	// The index of the current color scheme
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Colors)
	int CurrentColorSchemeIndex;

	// The current list of colors the character model is using
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<int> CurrentColors;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Set the character's headgear
	UFUNCTION(BlueprintCallable)
	void SetHeadgear(int Index);

	// Apply the next Headgear in the list, 1 for next, -1 for previous
	UFUNCTION(BlueprintCallable)
	void ApplyNextHeadgear(int Offset);

	// Apply a specific color to current headgear
	UFUNCTION(BlueprintCallable)
	void ApplyHeadgearColor(int ColorIndex, int MeshIndex);

	// Apply a specific color to a specific part of the character model
	void ApplyColor(int ColorIndex, int MeshIndex);

	// Change a character model's color scheme and apply the colors
	UFUNCTION(BlueprintCallable)
	void ApplyColorScheme(FColorScheme ColorScheme);

	// Change a character model's color scheme by index
	UFUNCTION(BlueprintCallable)
	void ApplyColorSchemeByIndex(int Index);

	// Apply the next Color Scheme in the list, 1 for next, -1 for previous
	UFUNCTION(BlueprintCallable)
	void ApplyNextColorSchemeByOffset(int Offset);

};
