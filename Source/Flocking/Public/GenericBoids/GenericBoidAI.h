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
	void RightVectorMovement(bool bTraceHit, float Tick);


	
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bShouldStop;
	bool bShouldTurn;
};
