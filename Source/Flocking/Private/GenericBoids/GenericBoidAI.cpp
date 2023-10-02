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

}

// Called to bind functionality to input
void AGenericBoidAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

