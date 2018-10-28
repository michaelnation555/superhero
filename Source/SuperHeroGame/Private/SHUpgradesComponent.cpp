// Fill out your copyright notice in the Description page of Project Settings.

#include "SHUpgradesComponent.h"
#include "SHCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SHHealthComponent.h"
#include "SHEnergyComponent.h"

// Sets default values for this component's properties
USHUpgradesComponent::USHUpgradesComponent()
{
	UpgradePoints = 0;
}


// Called when the game starts
void USHUpgradesComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Upgrade sprint speed
void USHUpgradesComponent::UpgradeSprintSpeed(float increase)
{
	if (UpgradePoints <= 0)
		return;
	UpgradePoints--;
	ASHCharacter* MyCharacter = Cast<ASHCharacter>(GetOwner());
	MyCharacter->MaxSprintSpeed += increase;

	//FString Message = "Sprint Speed: ";
	//Message += FString::SanitizeFloat(MyCharacter->MaxSprintSpeed);
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, Message);
}

// Upgrade jump strength
void USHUpgradesComponent::UpgradeJumpStrength(float increase)
{
	if (UpgradePoints <= 0)
		return;
	UpgradePoints--;
	ASHCharacter* MyCharacter = Cast<ASHCharacter>(GetOwner());
	MyCharacter->MaxJumpCharge += increase;

	//FString Message = "Jump Strength: ";
	//Message += FString::SanitizeFloat(MyCharacter->MaxJumpCharge);
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, Message);
}

// Upgrade fly speed
void USHUpgradesComponent::UpgradeFlySpeed(float increase)
{
	if (UpgradePoints <= 0)
		return;
	UpgradePoints--;
	ASHCharacter* MyCharacter = Cast<ASHCharacter>(GetOwner());
	MyCharacter->GetCharacterMovement()->MaxFlySpeed += increase;

	//FString Message = "Fly Speed: ";
	//Message += FString::SanitizeFloat(MyCharacter->GetCharacterMovement()->MaxFlySpeed);
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, Message);
}

// Upgrade max health
void USHUpgradesComponent::UpgradeMaxHealth(float increase)
{
	if (UpgradePoints <= 0)
		return;
	UpgradePoints--;
	ASHCharacter* MyCharacter = Cast<ASHCharacter>(GetOwner());
	TArray<USHHealthComponent*> HealthComps;
	MyCharacter->GetComponents<USHHealthComponent>(HealthComps);
	if (HealthComps[0] != NULL)
	{
		HealthComps[0]->MaxHealth += increase;
		HealthComps[0]->CurrentHealth = HealthComps[0]->MaxHealth; // Heal to full health
	}

	//FString Message = "Max Health: ";
	//Message += FString::SanitizeFloat(HealthComps[0]->MaxHealth);
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, Message);
}

// Upgrade max energy
void USHUpgradesComponent::UpgradeMaxEnergy(float increase)
{
	if (UpgradePoints <= 0)
		return;
	UpgradePoints--;
	ASHCharacter* MyCharacter = Cast<ASHCharacter>(GetOwner());
	TArray<USHEnergyComponent*> EnergyComps;
	MyCharacter->GetComponents<USHEnergyComponent>(EnergyComps);
	if (EnergyComps[0] != NULL)
		EnergyComps[0]->MaxEnergy += increase;

	//FString Message = "Max Energy: ";
	//Message += FString::SanitizeFloat(EnergyComps[0]->MaxEnergy);
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, Message);
}
