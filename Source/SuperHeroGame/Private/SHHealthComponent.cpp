// Fill out your copyright notice in the Description page of Project Settings.

#include "SHHealthComponent.h"
#include "SHCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USHHealthComponent::USHHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default Maximum Health
	MaxHealth = 100.0f;
	Dead = false;
}

// Called when the game starts
void USHHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set current health to maximum
	CurrentHealth = MaxHealth;
}

// Handle event when take damage
void USHHealthComponent::Damage(float damage)
{
	CurrentHealth -= damage;
	UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetOwner()->GetActorLocation());

	if (CurrentHealth <= 0 && !Dead) // You died
	{
		CurrentHealth = 0;
		Death();
	}
}

// Heal the character
void USHHealthComponent::Heal(float heal)
{
	CurrentHealth += heal;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}

// Die when health reaches zero
void USHHealthComponent::Death()
{
	//FString Message = "You died";
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, Message);
	Dead = true;
	ASHCharacter* character = (ASHCharacter*)GetOwner();
	character->GetMesh()->SetSimulatePhysics(true);
	character->GetController()->SetIgnoreMoveInput(true);
	TArray<UCapsuleComponent*> children;
	character->GetComponents<UCapsuleComponent>(children);
	if (children[0] != NULL)
	{
		children[0]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	GetOwner()->SetLifeSpan(5);
	if (Pickup != NULL)
		GetWorld()->SpawnActor<AActor>(Pickup, character->GetActorLocation(), FRotator::ZeroRotator);
}
