// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHPickup.h"
#include "SHUpgradePickup.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHEROGAME_API ASHUpgradePickup : public ASHPickup
{
	GENERATED_BODY()
	
public:
	// Detects collision when character overlaps the sphere component
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
