// Fill out your copyright notice in the Description page of Project Settings.

#include "SHItem.h"

// Sets default values
ASHItem::ASHItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = TEXT("Item Name");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASHItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASHItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASHItem::StartUse()
{
	FString Message = "Item Used!";
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, Message);
}

void ASHItem::EndUse()
{
	// do nothing
}
