// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericBoidAI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Team.h"
#include "GenericAIController.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKING_API AGenericAIController : public AAIController
{
	GENERATED_BODY()

public:

	AGenericAIController();

	UPROPERTY(EditAnywhere)
	class AGenericBoidAI* Boid;
	
	void BasicMovement();

	
protected:
	// Data Storage.
	UPROPERTY(EditAnywhere)
	UBlackboardComponent* BBComponent;

	// Assets that accesses Data and executes logic.
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BT;

	// Running Component attached to AI (Refers to BT).
	UPROPERTY(EditAnywhere)
	UBehaviorTreeComponent* BTComp;


private:
	// Stored for later, Possibly never used.
	
	// Ai's Sight.
	UPROPERTY(EditAnywhere,Category=Perception)
	TObjectPtr<UAISenseConfig_Sight> Sight_Config;

	// Detect if Actor is in the Same team.
	UPROPERTY(EditAnywhere,Category=Perception)
	TObjectPtr<UAISenseConfig_Team> Team_Config;


public:
	
	virtual void Tick(float DeltaTime) override;

	


	
};
