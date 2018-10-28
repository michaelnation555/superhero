// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHPickup.h"
#include "GameFramework/Actor.h"
#include "SHItem.h"
#include "SHItemPickup.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHItemPickup : public ASHPickup
{
	GENERATED_BODY()
	
public:
	// The item the character will have added to inventory when picked up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = pickup)
	TSubclassOf<ASHItem> PickupItem;

	// Detects collision when character overlaps the sphere component
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
