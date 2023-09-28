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

	AGenericAIController(FObjectInitializer const& ObjectInitializer);

	virtual void BeginPlay() override;

	void Movement();

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	// Data Storage.
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBlackboardComponent> BBComponent;

	// Assets that accesses Data and executes logic.
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BT;

	// Running Component attached to AI (Refers to BT).
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BTComp;

	class AGenericBoidAI* GenBoid = nullptr;
	
private:
	// Stored for later, Possibly never used.
	
	// Ai's Sight.
	UPROPERTY(EditAnywhere,Category=Perception)
	TObjectPtr<UAISenseConfig_Sight> Sight_Config;

	// Detect if Actor is in the Same team.
	UPROPERTY(EditAnywhere,Category=Perception)
	TObjectPtr<UAISenseConfig_Team> Team_Config;


public:
	// Array of boids.
	TArray<AGenericBoidAI> Agents;
	// Index of the current states of each boid is stored.
	int32 CurrentStatesIndex;
	// Index of previous states of each boid is stored.
	int32 PreviousStatesIndex;
	// Weight factor for cohesion.
	int32 kCoh;
	// Weight factor for Seperation.
	int32 kSep;
	// Weight factor for alignment.
	int32 kAlign;
	// Radius neighbours are sought for cohesion.
	int rCoh;
	// Radius neighbours are sought for seperation.
	int rSep;
	// Radius neighbours are sought for alignment.
	int rAlign;
	// Max acceleration.
	int MaxAcel;
	// Max speed.
	int MaxVel;
	// Boundries of area boid can move.
	int MapSize;
	// Elapsed time since last calulation.
	int32 DeltaTime;
	// Param that indicates which mode the loop will run.
	bool isSinglethread;
	// Checks if the Boid is moving.
	bool Idle;
	// 
	
};
