// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/GenericAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Flocking\Public\GenericBoids\GenericBoidAI.h"
#include "GameFramework/CharacterMovementComponent.h"

AGenericAIController::AGenericAIController(FObjectInitializer const& ObjectInitializer)
{
	//MaxAcel = GenBoid->GetCharacterMovement()->MaxAcceleration;
	
}

void AGenericAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGenericAIController::Movement()
{
	/*int Speed = 50;
	FVector Location = GenBoid->GetActorLocation();
	Location += GenBoid->GetActorForwardVector() * Speed;
	GenBoid->SetActorLocation(Location);*/
}

void AGenericAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Movement();
}
