// Fill out your copyright notice in the Description page of Project Settings.

#include "SHItemPickup.h"
#include "SHCharacter.h"
#include "Kismet/GameplayStatics.h"

// Detects collision when character overlaps the sphere component
void ASHItemPickup::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ASHCharacter* Character = Cast<ASHCharacter>(OtherActor);
	if (Character)
	{
		if (Character->InventoryComponent->PickupItem(PickupItem))
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
			Destroy();
		}
	}
}