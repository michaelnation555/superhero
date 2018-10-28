// Fill out your copyright notice in the Description page of Project Settings.

#include "SHPickup.h"

// Sets default values
ASHPickup::ASHPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(SphereComp);

	RotationSpeed = FRotator(0, 0, 100);
}

// Called when the game starts or when spawned
void ASHPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(RotationSpeed * DeltaTime);
}
