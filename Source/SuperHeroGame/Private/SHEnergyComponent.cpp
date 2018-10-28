// Fill out your copyright notice in the Description page of Project Settings.

#include "SHEnergyComponent.h"

// Sets default values for this component's properties
USHEnergyComponent::USHEnergyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default Maximum Energy
	MaxEnergy = 100.0f;

	// Default Regeration Rate
	RegenerationRate = 10.0f;

	// Regenerate Energy by Default
	IsRegenerate = true;
}

// Called when the game starts
void USHEnergyComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set current energy to maximum
	CurrentEnergy = MaxEnergy;
}

// Called every frame
void USHEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Regenerate Energy
	if (IsRegenerate)
		Regenerate(GetOwner()->GetWorld()->GetDeltaSeconds() * RegenerationRate);
}

// Consume an amount of Energy
void USHEnergyComponent::Consume(float energy)
{
	//FString Message = "Consuming Energy...";
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, Message);

	CurrentEnergy -= energy;
	if (CurrentEnergy < 0)
		CurrentEnergy = 0;
}

// Regenerate an amount of Energy
void USHEnergyComponent::Regenerate(float energy)
{
	CurrentEnergy += energy;
	if (CurrentEnergy > MaxEnergy)
		CurrentEnergy = MaxEnergy;
}
