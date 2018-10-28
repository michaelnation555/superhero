// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHEnergyComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHEROGAME_API USHEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USHEnergyComponent();

	// Maximum Energy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float MaxEnergy;

	// Current Energy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Energy)
	float CurrentEnergy;

	// Energy regeneration rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float RegenerationRate;

	// Regenerate Energy if true
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	bool IsRegenerate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Consume an amount of Energy
	UFUNCTION(BlueprintCallable)
	void Consume(float energy);

	// Regenerate an amount of Energy
	UFUNCTION(BlueprintCallable)
	void Regenerate(float energy);

};
