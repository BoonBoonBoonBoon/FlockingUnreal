// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Flocking/Public/GenericBoids/GenericBoidAI.h"
#include "AIModule\Classes\BehaviorTree\BTTaskNode.h"
#include "Flocking/Public/GenericBoids/GenericAIController.h"
#include "BTTask_RoamMap.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKING_API UBTTask_RoamMap : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	// Execute task function
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	// Gives node a name
	virtual FString GetStaticDescription() const override;

	UBTTask_RoamMap();
	
	void MoveForward(FVector ForwardVector, int Acceleration, int Velocity);

	void AvoidOb(FVector Ob);

	class AGenericBoidAI* GenericBoid = nullptr;

protected:


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
	//
	bool Idle;
	
};
