// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHPickup.h"
#include "SHHealthPickup.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHHealthPickup : public ASHPickup
{
	GENERATED_BODY()

public:
	ASHHealthPickup();

	// Heal amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float heal;

	// Detects collision when character overlaps the sphere component
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
