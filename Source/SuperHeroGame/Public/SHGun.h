// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHItem.h"
#include "SHGun.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHGun : public ASHItem
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ASHGun();

	// Maximum capacity for ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	int Capacity;

	// Current ammo in the magazine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	int CurrentAmmo;

	// Rate of Fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float RateofFire;

	// Range of bullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float Range;

	// Damage of shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float Damage;

	// Automatic Fire or Semi-Auto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	bool IsAutomatic;

	// Is the gun currently being fired?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
	bool IsFiring;

	// Name of the bullet spawn socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	FName BulletSpawnSocketName;

	// Name of the Tracer effect parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	FName TracerTargetName;

	// Sound effect
	UPROPERTY(EditDefaultsOnly, Category = Gun)
	USoundBase* FireSound;

	// Muzzle effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gun)
	UParticleSystem* MuzzleEffect;

	// Tracer effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gun)
	UParticleSystem* TracerEffect;

	FTimerHandle TimerHandle_TimeBetweenShots;

	FTimerHandle TimerHande_TimeToReload;

	float LastFireTime;

	// Start firing the Gun
	virtual void StartUse() override;

	// Stop firing the Gun
	virtual void EndUse() override;

	// Fire the Gun once
	void Fire();

	// Play sound and visual effects when fired
	void PlayFireEffects(FVector TraceEnd);

};
