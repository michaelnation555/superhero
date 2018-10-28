// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHItem.h"
#include "SHInventoryComponent.generated.h"

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHEROGAME_API USHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USHInventoryComponent();

	// Currently selected Item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	ASHItem* CurrentItem;

	// Current slot number
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	int CurrentSlot;

	// Number of Items
	const int ITEMS = 5; // 0 = default, 1,2,3,4 = items

	// Starting items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	TArray<TSubclassOf<ASHItem>> StartingItems;

	// Item Slots
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	TArray<ASHItem*> Items;

	// Right Hand Socket Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	FName RightHandSocket;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Equip an item from a given slot number
	UFUNCTION(BlueprintCallable)
	void EquipItem(int slot);

	// Create the item object in the character's hand
	ASHItem* SpawnItemInHand(TSubclassOf<ASHItem> item, int index);

	// Hide the item and disable collision, used for de-equipping
	void EnableItem(bool enable);

	// Add a new item to inventory, return false if inventory was full
	bool PickupItem(TSubclassOf<ASHItem> item);

	// Remove an item from inventory
	UFUNCTION(BlueprintCallable)
	void DropItem(int index);

};
