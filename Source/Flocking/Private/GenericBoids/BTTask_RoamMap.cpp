// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/BTTask_RoamMap.h"

#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTask_RoamMap::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	

	FVector ForwardV = GenericBoid->GetActorForwardVector();
	GenericBoid->AddMovementInput(ForwardV,1, false);
	
	return EBTNodeResult::Succeeded;
}


FString UBTTask_RoamMap::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
}

UBTTask_RoamMap::UBTTask_RoamMap()
{
	NodeName = "Roam Location";
	BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_RoamMap, BlackboardKey));

	
}

void UBTTask_RoamMap::MoveForward(FVector ForwardVector, int Acceleration, int Velocity)
{

	// Move the actor by the value given, this value will move a certain amount of distance.

	//GenericBoid->AddMovementInput(ForwardVector,0, false);
	
}

void UBTTask_RoamMap::AvoidOb(FVector Ob)
{
}
