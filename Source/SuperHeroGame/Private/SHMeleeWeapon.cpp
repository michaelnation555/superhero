// Fill out your copyright notice in the Description page of Project Settings.

#include "SHMeleeWeapon.h"
#include "SHCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
ASHMeleeWeapon::ASHMeleeWeapon()
{
	Name = TEXT("MeleeWeapon");

	// Set default values for Melee
	Damage = 40.0f;
}

void ASHMeleeWeapon::StartUse()
{
	ASHCharacter* OwnerController = Cast<ASHCharacter>(GetOwner());
	OwnerController->StartMeleeAttack();
}

void ASHMeleeWeapon::EndUse()
{

}
