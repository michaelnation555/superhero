// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "SHPickup.generated.h"

UCLASS()
class SUPERHEROGAME_API ASHPickup : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASHPickup();

	// The mesh of the item to be pickedup
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = pickup)
	UStaticMeshComponent* MeshComp;

	// The sphere component used for detecting collision with character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = pickup)
	USphereComponent* SphereComp;

	// The speed that the pickup will rotate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = pickup)
	FRotator RotationSpeed;

	// Sound effect played when picked up
	UPROPERTY(EditDefaultsOnly, Category = pickup)
	USoundBase* PickupSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
