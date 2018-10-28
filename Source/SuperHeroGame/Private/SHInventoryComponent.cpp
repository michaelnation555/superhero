// Fill out your copyright notice in the Description page of Project Settings.

#include "SHInventoryComponent.h"
#include "SHItem.h"
#include "SHCharacter.h"
#include "OutputDeviceNull.h"

// Sets default values for this component's properties
USHInventoryComponent::USHInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// Each character has a default weapon (index 0) and 4 weapon slots
	StartingItems.SetNum(ITEMS);
	Items.SetNum(ITEMS);

	CurrentSlot = 0; // Default item slot

	RightHandSocket = TEXT("Right Hand Item Socket");
}

// Called when the game starts
void USHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < ITEMS; ++i)
	{
		Items[i] = SpawnItemInHand(StartingItems[i], i);
	}
	
	EquipItem(0);
}

// Equip an item from a given slot number
void USHInventoryComponent::EquipItem(int slot)
{
	if (slot >= ITEMS) // Error, out of range
		return;
	
	if (Items[slot] == NULL || slot == CurrentSlot) // Equip default item (slot = 0)
	{
		EnableItem(false); // disable current item before switching
		CurrentItem = Items[0];
		EnableItem(true);
		CurrentSlot = 0;

		return;
	}

	EnableItem(false); // disable current item before switching
	CurrentItem = Items[slot];
	EnableItem(true);
	CurrentSlot = slot;
}

ASHItem* USHInventoryComponent::SpawnItemInHand(TSubclassOf<ASHItem> item, int index)
{
	ASHItem* NewItem = GetWorld()->SpawnActor<ASHItem>(item, FVector::ZeroVector, FRotator::ZeroRotator);
	if (NewItem)
	{
		ASHCharacter* MyCharacter = Cast<ASHCharacter>(GetOwner());
		NewItem->SetOwner(MyCharacter);
		NewItem->AttachRootComponentTo(MyCharacter->GetMesh(), RightHandSocket, EAttachLocation::SnapToTarget, true);
		NewItem->SetActorHiddenInGame(true);
		NewItem->SetActorEnableCollision(false);
		NewItem->SetActorTickEnabled(false);

		// Update inventory screen
		MyCharacter->UpdateInventoryScreen(index, NewItem->Icon);

		return NewItem;
	}

	return NULL;
}

// Hide the item and disable collision, used for de-equipping
void USHInventoryComponent::EnableItem(bool enable)
{
	if (CurrentItem)
	{
		CurrentItem->SetActorHiddenInGame(!enable);
		CurrentItem->SetActorEnableCollision(enable);
		CurrentItem->SetActorTickEnabled(enable);
	}
}

// Add a new item to inventory, return false if inventory was full
bool USHInventoryComponent::PickupItem(TSubclassOf<ASHItem> item)
{
	// Find an empty slot for the picked up item
	for (int i = 1; i < ITEMS; i++)
	{
		if (Items[i] == NULL)
		{
			Items[i] = SpawnItemInHand(item, i);
			return true;
		}
	}
	return false; // Did not have an empty slot
}

// Remove an item from inventory
void USHInventoryComponent::DropItem(int index)
{
	//FString Message = "Dropping Item...";
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, Message);

	if (index >= ITEMS || index <= 0 || Items[index] == NULL)
		return;
	EquipItem(0);
	Items[index]->Destroy();
	Items[index] = nullptr;
}
