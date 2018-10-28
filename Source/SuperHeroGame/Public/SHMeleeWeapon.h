// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHItem.h"
#include "SHMeleeWeapon.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHMeleeWeapon : public ASHItem
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ASHMeleeWeapon();

	// The box collider that will detect melee attacks
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Melee)
	//class UBoxComponent* BoxComponent;
	
	// Damage of shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Melee)
	float Damage;

	// Start striking with the Melee Weapon
	virtual void StartUse() override;

	// Stop striking with the Melee Weapon
	virtual void EndUse() override;

};
