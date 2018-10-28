// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SHItem.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASHItem();

	// Name of the Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FName Name;

	// Type of animation the character uses i.e. "Unarmed", "Pistol", "Sword"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FName AnimationType;

	// Static Mesh of the Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	UStaticMeshComponent* MeshComponent;

	// Icon for inventory screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	UTexture2D* Icon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Use the item i.e. attack, shoot, throw etc...
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void StartUse();

	// Stop using the item i.e. stop automatic fire... or stop charging weapon
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void EndUse();
};
