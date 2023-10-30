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

	//TArray<AGenericBoidAI> Boids;
	
	// Creates 90 Degree Peripheral vision with traces. 
	void ForwardTrace(float DeltaTime);

	void Radius(float DeltaTime);
	
	// Checks if the Boid is rotating.
	void TurnVector(bool IsRight);
	
	// Moves the AI forward.
	void ForwardMovement(float Speed, float DeltaTime, bool isTurning);

	
	/////// New Vars and functs 
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
	
	// Boids Steers to stay near other boids.
	//void Cohesion(TArray<AGenericBoidAI> Boids);
	// Boids Steers to avoid collision with other boids.
	//void Alignment(TArray<AGenericBoidAI> Boids);
	// boids Steers toward the same direction as others.
	//void Seperation(TArray<AGenericBoidAI> Boids);

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
	
	//FTimerHandle RotationTimerHandle;

	// Starting Rotation of actor 
	FRotator StartRotation = GetActorRotation();

	// Target Rotation (90 Degrees)
	//const FRotator LeftRotation = FRotator(0, LeftTurnRate, 0);

	// The progress of the turn (0 to 1)
	float TurnAmount = 90.f;
	float RotationSpeed = 0.8f;
	
	//int32 RightTurnRate = 0;
	//int32 LeftTurnRate = 0;

	float StartingRot;
	
	bool bIsActiveRotating = false;
	bool bIsRotatingRight = false;
	
	bool bShouldStop;
	bool bShouldTurn;
};


//void CheckRotation(int32 Angle, float DeltaTime, bool bHit);

// Turns the Actor Right
//void RightVectorMovement(bool bTraceHit, float DeltaTime, int32 TurnRate);
//	void UpdateTraceRight(bool bTraceHit, float DeltaTime, int32 TurnRate);