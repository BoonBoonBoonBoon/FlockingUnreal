// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/GenericBoidAI.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "GeometryTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AGenericBoidAI::AGenericBoidAI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Head = CreateDefaultSubobject<USphereComponent>("HeadComp");
	Head->SetupAttachment(RootComponent);

	HeadShape = CreateDefaultSubobject<UStaticMeshComponent>("HeadShape");
	HeadShape->SetupAttachment(Head);

	// Radius 
	float R = 300.f;
	//float MaxSpeed = 

	
}

int bIsCurrentlyRotating;
// Creates Peripheral Vision
void AGenericBoidAI::ForwardTrace(float DeltaTime)
{
	// Get Actors Current rotation
	FRotator ActorRotation = GetActorRotation();

	// 90 Degree angle set Vector for every 10 degrees (-45 left, 45 right, and 10 for every Angle)
	for (int32 Angle = -45; Angle <= 45; Angle += 10)
	{
		FRotator RotatedVector = ActorRotation + FRotator(0, Angle, 0);
		FVector DirectionVector = RotatedVector.Vector();

		FHitResult Hit;
		FVector StartLoc = GetActorLocation() + (GetActorForwardVector() * 70);
		constexpr float TraceDistance = 250.f;
		FCollisionQueryParams TraceParams;
		TraceParams.ClearIgnoredActors();


		FVector Endloc = StartLoc + DirectionVector * TraceDistance;

		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, Endloc, ECC_Camera, TraceParams);
		if (bHit)
		{
			
			// Calculate the box's dimensions & Location
			FVector BoxExtents(10.0f, 10.0f, 10.0f);
			FVector BoxLocation = Endloc;

			// Draw Debug Line
			DrawDebugLine(GetWorld(), StartLoc, Endloc, FColor::Red, false, -1, 0, 4);

			// Draw the debug box
			DrawDebugBox(GetWorld(), BoxLocation, BoxExtents, FColor::Orange, false, -1, 0, 4);
			
			TurnVector(Angle < 0);
			break;
		}
	}
}

/*void AGenericBoidAI::Radius(float DeltaTime)
{
	
}*/

void AGenericBoidAI::TurnVector(bool IsRight)
{
	bIsActiveRotating = true;
	bIsRotatingRight = IsRight;

	StartingRot = GetActorRotation().Yaw;
}

void AGenericBoidAI::ForwardMovement(float Speed, float DeltaTime, bool isTurning)
{
	/*if (isTurning)
	{
		Acceleration(DeltaTime);
		//Speed = 200.f;
	}
	else if (!isTurning)
	{
		Acceleration(DeltaTime);
		//Speed = 200.f;
	}*/

	Acceleration(DeltaTime,isTurning);
	
	// Where Actor currently is 
	FVector CurrentLocation = GetActorLocation();
	// adds the forward vector which is multiplied by the speed and the tick
	
	// Destination //
	CurrentLocation += GetActorForwardVector() * TargetSpeed * DeltaTime;
	// Sets its new location
	SetActorLocation(CurrentLocation);
}

void AGenericBoidAI::Acceleration(float DeltaTime, bool isTurning)
{
	/*AGenericBoidAI* BoidAI = nullptr;
	const FVector Accel = BoidAI->GetCharacterMovement()->GetCurrentAcceleration();
	UE_LOG(LogTemp, Warning, TEXT("Acceleration: %s"), *Accel.ToString());*/

	AActor* Boid = GetOwner();
	// Calculate the new acceleration based on interpolation.
	//CurrentAcceleration = FMath::VInterpTo(CurrentAcceleration, TargetAcceleration, DeltaTime, AccelerationChangeSpeed);
	// Print the values of CurrentAcceleration and Boid
	
	//UE_LOG(LogTemp, Warning, TEXT("Boid: %s"), *Boid->GetName());

	// Apply new acceleration to actor.
	//Boid->AddActorLocalOffset(CurrentAcceleration * DeltaTime);


	if(isTurning)
	{
		//  Decrease Acceleration and speed for turning 
		CurrentAcceleration = FMath::VInterpTo(CurrentAcceleration, TargetAcceleration, DeltaTime, TurnDecelerationRate);
		UE_LOG(LogTemp, Warning, TEXT("TurnDecelerationRate: %s"), *CurrentAcceleration.ToString());
	} else
	{
		// increase acceleration and speed when not turning 
		CurrentAcceleration = FMath::VInterpTo(CurrentAcceleration, TargetAcceleration, DeltaTime, AccelerationRate);
		UE_LOG(LogTemp, Warning, TEXT("AccelerationRate: %s"), *CurrentAcceleration.ToString());
	}
	
	Boid->AddActorLocalOffset(CurrentAcceleration * DeltaTime);

	
}


// Called when the game starts or when spawned
void AGenericBoidAI::BeginPlay()
{ 
	Super::BeginPlay();
	
	TArray<AGenericBoidAI*> Boids;
    
	// Populate Boids array with other boids in the world

	//Flock(Boids);
}

// Called every frame
void AGenericBoidAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForwardTrace(DeltaTime);
	//Radius(DeltaTime);
	//Acceleration(DeltaTime, );

		
	// Acceleration has something to do with the speed variable
	// Is acceleration the same as velocity??
	// Maybe use velocity instead > Since the actor will need to be able to slow down and increase speed when its near to its traces object.. .. .
	
	//ForwardMovement(NULL, DeltaTime, true);

	
	// Checks for active rotation.
	if (bIsActiveRotating)
	{
		ForwardMovement(NULL, DeltaTime, true);
		int Direction = bIsRotatingRight ? 1 : -1;
		AddActorWorldRotation(FRotator(0, Direction * RotationSpeed, 0));
		bIsActiveRotating = GetActorRotation().Yaw - StartingRot > TurnAmount;
	}else
	{
		ForwardMovement(NULL, DeltaTime, false);
	}
}
