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
	// Sets default values for this character's properties
	AGenericBoidAI();
	
	// Creates 90 Degree Peripheral vision with traces. 
	void ForwardTrace(float DeltaTime);


	/////// COHESION //////////////////////////////////////////////////////////////////
	void RadiusCohTrace(int32 NumTraces, float RadiusCoh);
	// Overrides the movement pattern to follow the boid with the highest weight
	void RadiusCohMovement();
	
	void CohWeight(AActor* ActorHit, float Weight);
	// Creates a empty Array that will store refrences to Boids 
	TArray<AGenericBoidAI*> BoidArray;

	// Creates an empty TMap that will store the key of type Boid, And a float value. 
	// TMap is a key,value; pair. Similar to an array however instead of one object you can store pairs of data
	// I.e Actor, float = GenericBoid, 4; Data Structure little bit like a struct.
	TMap<AGenericBoidAI*, float> BoidWeightMap;
	
	// Weight of a independent boid 
	float DefaultWeight = 1.f;
	float CurrentWeight;
	
	// The Increase of weight from local Boids 
	float WeightIncease = 0.25f;
	bool bFoundBoidTofollow = false;
	//////////////////////////////////////////////////////////////////////////////

///////////////////SEPARATION////////////////////////////////////////////////////

	void RadiusSepTrace(int32 NumTraces, float RadiusSep);
	



///////////////////////////////////////////////////////////////////////////////////
	
	// Checks if the Boid is rotating.
	void TurnVector(bool IsRight, float DistanceToObj);
	// Moves the AI forward.
	void ForwardMovement(float Speed, float DeltaTime, bool isTurning);
	
	/////// ACCELERATION///////////////////////////////////////////////////////////////
	void Seek(FVector Target);
	float MaxSpeed = 200.f;
	FVector Velocity = FVector::ZeroVector;
	FVector Accel = FVector::ZeroVector;
	void ApplyForce(FVector Force);
	// Controls the Boids Current Acceleration & Deceleration 
	void Acceleration(float DeltaTime, bool isTurning);
	// Target Speed 
	float TargetSpeed = 200.f;
	// Acceleration Boid wants to reach
	FVector TargetAcceleration = FVector(300.0f, 0.0f, 0.0f);
	// Stored for Interpolation between current & Target (ZeroVector Sets all values to zero)
	FVector CurrentAcceleration = FVector::ZeroVector;
	float AccelerationRate = 100.f;
	float TurnDecelerationRate = 300.f;
		
	// The value of what the acceleration speed will increase by
	//float AccelerationChangeSpeed = 0.5f;
	///////////////////////////////////////////////////////////////////////////////////////
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* Head;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* HeadShape;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Getter for boid rotation 
	FRotator GetBoidRotation(const AActor* Actor){return GetActorRotation(); }

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Starting Rotation of actor 
	FRotator StartRotation = GetActorRotation();
	
	// The progress of the turn (0 to 1)
	float TurnAmount = 90.f;
	float RotationSpeed = 0.8f;
	
	float StartingRot;
	
	bool bIsActiveRotating = false;
	bool bIsRotatingRight = false;
	
	bool bShouldStop;
	bool bShouldTurn;
};

