// Fill out your copyright notice in the Description page of Project Settings.

#include "SHGun.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "SHCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASHGun::ASHGun()
{
	Name = TEXT("Gun");

	// Set default values for firing
	Capacity = 10;
	CurrentAmmo = 10;
	RateofFire = 0.1f;
	Range = 10000;
	Damage = 20.0f;
	IsAutomatic = true;
	IsFiring = false;
	BulletSpawnSocketName = TEXT("BulletSpawn");
	TracerTargetName = TEXT("Target");
}

void ASHGun::StartUse()
{
	IsFiring = true;

	if (IsAutomatic)
	{
		float FirstDelay = FMath::Max(LastFireTime + RateofFire - GetWorld()->TimeSeconds, 0.0f);
		GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &ASHGun::Fire, RateofFire, true, FirstDelay);
	}
	else
		Fire();
}

void ASHGun::EndUse()
{
	IsFiring = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void ASHGun::Fire()
{
	AActor* MyOwner = GetOwner();

	if (CurrentAmmo > 0 && MyOwner)
	{
		--CurrentAmmo;

		// Setup direction of line trace
		FVector BulletSpawnLocation = MeshComponent->GetSocketLocation(BulletSpawnSocketName);
		FRotator CharacterRotation = GetOwner()->GetActorRotation();
		FVector ShotDirection = CharacterRotation.Vector();
		FVector TraceEnd = BulletSpawnLocation + (ShotDirection * Range);

		// Setup collision parameters
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		//QueryParams.bReturnPhysicalMaterial = true;

		// If character is aiming, draw trace from camera
		ASHCharacter* MyCharacter = Cast<ASHCharacter>(GetOwner());
		if (MyCharacter && MyCharacter->Aiming)
		{
			ShotDirection = MyCharacter->FollowCamera->GetComponentRotation().Vector();
			TraceEnd = MyCharacter->FollowCamera->GetComponentLocation() + (ShotDirection * Range);
			FHitResult CameraHit;
			if (GetWorld()->LineTraceSingleByChannel(CameraHit, MyCharacter->FollowCamera->GetComponentLocation(), TraceEnd, ECC_GameTraceChannel1, QueryParams))
			{
				TraceEnd = CameraHit.ImpactPoint;
			}
		}

		FVector TracerEndPoint = TraceEnd; // Particle "Target" parameter

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, BulletSpawnLocation, TraceEnd, ECC_GameTraceChannel1, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();

			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, Hit, MyOwner->GetInstigatorController(), MyOwner, DamageType);

			TracerEndPoint = Hit.ImpactPoint;

			//DrawDebugLine(GetWorld(), BulletSpawnLocation, TraceEnd, FColor::Red, false, 5.0f, 0, 1.0f);
		}

		// Play sound and visual effects
		PlayFireEffects(TracerEndPoint);
	}
}

void ASHGun::PlayFireEffects(FVector TraceEnd)
{
	// Play Sound effect
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// Play Muzzle effect
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComponent, BulletSpawnSocketName);
	}

	// Play Tracer effect
	if (TracerEffect)
	{
		FVector MuzzleLocation = MeshComponent->GetSocketLocation(BulletSpawnSocketName);

		UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
		if (TracerComp)
		{
			TracerComp->SetVectorParameter(TracerTargetName, TraceEnd);
		}
	}
}
