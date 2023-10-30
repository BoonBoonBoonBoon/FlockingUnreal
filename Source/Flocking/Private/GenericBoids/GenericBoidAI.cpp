// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/GenericBoidAI.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Math/Vector.h"
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
	for (int32 Angle = -100; Angle <= 100; Angle += 5)
	{
		FRotator RotatedVector = ActorRotation + FRotator(0, Angle, 0);
		FVector DirectionVector = RotatedVector.Vector();

		FHitResult Hit;
		FVector StartLoc = GetActorLocation() + (GetActorForwardVector() * 70);
		float TraceDistance = 250.f;
		FCollisionQueryParams TraceParams;
		TraceParams.ClearIgnoredActors();
		
		FVector Endloc = StartLoc + DirectionVector * TraceDistance;

		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, Endloc, ECC_Camera, TraceParams);
		if (bHit)
		{
			// Calculate the distance to the hit object
			float DistanceToObstacle = (Hit.ImpactPoint - StartLoc).Size();
			// Calculate the box's dimensions & Location
			FVector BoxExtents(10.0f, 10.0f, 10.0f);
			FVector BoxLocation = Endloc;
	
			// Draw Debug Line
			DrawDebugLine(GetWorld(), StartLoc, Endloc, FColor::Red, false, -1, 0, 4);
			// Draw the debug box
			DrawDebugBox(GetWorld(), BoxLocation, BoxExtents, FColor::Orange, false, -1, 0, 4);
			// update the line trace with a new start location or distance
		
			
			TurnVector(Angle < 0, DistanceToObstacle);
			break;
		}
		
		
	}
}

void AGenericBoidAI::TurnVector(bool IsRight, float DistanceToObj)
{
	
	bIsActiveRotating = true;
	bIsRotatingRight = IsRight;

	StartingRot = GetActorRotation().Yaw;
	if (bIsActiveRotating)
	{
		constexpr float MaxSpeedToObj = 200.f;
		constexpr float MinSpeedToObj = 50.f;

		// Return a percentile value between 0 and 1
		float SpeedMultiplier = FMath::GetMappedRangeValueClamped(FVector2d(0.0f, DistanceToObj), FVector2D(1.0f, 0.0f), DistanceToObj);
		// Clamps the speed from 0 to 1 
		SpeedMultiplier = FMath::Clamp(SpeedMultiplier, 0.0f, 1.0f);
		// Interpolates the speed values and its change 
		const float NewSpeed = FMath::Lerp(MaxSpeedToObj, MinSpeedToObj, SpeedMultiplier);

		// Assign New Values 
		TargetSpeed = NewSpeed;
	} else
	{
		TargetSpeed = MaxSpeed;
	}
}

void AGenericBoidAI::ForwardMovement(float Speed, float DeltaTime, bool isTurning)
{
	
	//Acceleration(DeltaTime,isTurning);
	// Where Actor currently is 
	FVector CurrentLocation = GetActorLocation();
	// Destination 
	CurrentLocation += GetActorForwardVector() * Speed * DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), Speed);
	
	// Sets its new location
	SetActorLocation(CurrentLocation);
}

void AGenericBoidAI::Seek(FVector Target)
{

	/*FVector DesiredLoc = Target - GetActorLocation();
	DesiredLoc.Normalize();
	DesiredLoc *= MaxSpeed;

	FVector Steer = DesiredLoc - Velocity;

	ApplyForce(Steer);*/
}

void AGenericBoidAI::ApplyForce(FVector Force)
{
	//Accel += Force;
}

void AGenericBoidAI::Acceleration(float DeltaTime, bool isTurning)
{
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
	
	// Checks for active rotation.
	if (bIsActiveRotating)
	{
		ForwardMovement(TargetSpeed, DeltaTime, true);
		int Direction = bIsRotatingRight ? 1 : -1;
		AddActorWorldRotation(FRotator(0, Direction * RotationSpeed, 0));
		bIsActiveRotating = GetActorRotation().Yaw - StartingRot > TurnAmount;
	}else
	{
		ForwardMovement(TargetSpeed, DeltaTime, false);
	}
}



/*Velocity += Accel * DeltaTime;

Velocity = FVector::VectorPlaneProject(Velocity, FVector::UpVector);
Velocity = FVector::GetClampedToSize(Velocity, MaxSpeed);

FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
SetActorLocation(NewLocation);

Accel = FVector::ZeroVector;*/



/*
AActor* Boid = GetOwner();

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
*/
	
//Boid->AddActorLocalOffset(CurrentAcceleration * DeltaTime);



/*FVector TargetLoc = GetActorLocation();
// Destination 
TargetLoc += GetActorForwardVector();
Seek(TargetLoc);*/
	
//ForwardMovement(NULL, DeltaTime, true);
	
//Radius(DeltaTime);
//Acceleration(DeltaTime, );
	
// Acceleration has something to do with the speed variable
// Is acceleration the same as velocity??
// Maybe use velocity instead > Since the actor will need to be able to slow down and increase speed when its near to its traces object.. .. 
	