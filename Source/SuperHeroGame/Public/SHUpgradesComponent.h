// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHUpgradesComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHEROGAME_API USHUpgradesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USHUpgradesComponent();

	// Current number of skill points available for upgrades
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Upgrades)
	int UpgradePoints;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Upgrade sprint speed
	UFUNCTION(BlueprintCallable)
	void UpgradeSprintSpeed(float increase);

	// Upgrade jump strength
	UFUNCTION(BlueprintCallable)
	void UpgradeJumpStrength(float increase);

	// Upgrade fly speed
	UFUNCTION(BlueprintCallable)
	void UpgradeFlySpeed(float increase);

	// Upgrade max health
	UFUNCTION(BlueprintCallable)
	void UpgradeMaxHealth(float increase);

	// Upgrade max energy
	UFUNCTION(BlueprintCallable)
	void UpgradeMaxEnergy(float increase);

};
