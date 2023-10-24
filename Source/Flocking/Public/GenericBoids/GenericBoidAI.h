// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GenericBoidAI.generated.h"

UCLASS()
class FLOCKING_API AGenericBoidAI : public ACharacter
{
	GENERATED_BODY()

public:

	// TODO Get the steering sorted
	// after that setup the velocity and deceleration
	// once movement it set, move onto the cohesion func
	
	// Sets default values for this character's properties
	AGenericBoidAI();

	
	//Peripheral Vision
	void ForwardTrace();

	// Moves the AI forward
	void ForwardMovement(float Speed, float DeltaTime, bool isTurning);

	// Turns the Actor Right
	void RightVectorMovement(bool bTraceHit, float DeltaTime, int32 TurnRate);

	// Turns the Actor Left
	void LeftVectorMovement(bool bTraceHit, float DeltaTime, int32 TurnRate);

	
	void Cohesion();

	void Alignment();

	void Seperation();

	UPROPERTY(EditAnywhere)
	class USphereComponent* Head;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* HeadShape;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DelayedRotation();
	
public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FTimerHandle RotationTimerHandle;

	// Starting Rotation of actor 
	FRotator StartRotation = GetActorRotation();

	// Target Rotation (90 Degrees)

	const FRotator LeftRotation = FRotator(0, LeftTurnRate, 0);

	// The progress of the turn (0 to 1)
	float TurnProgress = 0.f;
	float RotationDelay = 4.f;
	
	int32 RightTurnRate = 0;
	int32 LeftTurnRate = 0;
	
	bool bShouldStop;
	bool bShouldTurn;
};
