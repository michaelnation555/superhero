// Fill out your copyright notice in the Description page of Project Settings.

#include "SHUpgradePickup.h"
#include "SHCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SHUpgradesComponent.h"

// Detects collision when character overlaps the sphere component
void ASHUpgradePickup::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ASHCharacter* Character = Cast<ASHCharacter>(OtherActor);
	if (Character)
	{
		APlayerController* playerController = Cast<APlayerController>(Character->GetController());
		if (playerController)
		{
			TArray<USHUpgradesComponent*> upgradeComps;
			Character->GetComponents<USHUpgradesComponent>(upgradeComps);
			if (upgradeComps[0] != NULL)
			{
				upgradeComps[0]->UpgradePoints++;
				UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
				Destroy();
			}
		}
	}
}