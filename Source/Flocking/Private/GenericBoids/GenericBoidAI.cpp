// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/GenericBoidAI.h"

// Sets default values
AGenericBoidAI::AGenericBoidAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AGenericBoidAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenericBoidAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * 500 * DeltaTime;
	SetActorLocation(Location);
	
	
}

