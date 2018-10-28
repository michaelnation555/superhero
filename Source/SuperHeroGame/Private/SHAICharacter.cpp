// Fill out your copyright notice in the Description page of Project Settings.

#include "SHAICharacter.h"


// Sets default values
ASHAICharacter::ASHAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASHAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASHAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

