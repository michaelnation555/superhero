// Fill out your copyright notice in the Description page of Project Settings.

#include "SHHealthPickup.h"
#include "SHCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SHHealthComponent.h"

// Sets default values
ASHHealthPickup::ASHHealthPickup()
{
	heal = 50.0;
}

// Detects collision when character overlaps the sphere component
void ASHHealthPickup::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ASHCharacter* Character = Cast<ASHCharacter>(OtherActor);
	if (Character)
	{
		TArray<USHHealthComponent*> healthComps;
		Character->GetComponents<USHHealthComponent>(healthComps);

		if (healthComps[0] != NULL)
		{
			healthComps[0]->Heal(heal);
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
			Destroy();
		}
	}
}