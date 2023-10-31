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
	
	
	
	
}


// Creates Peripheral Vision
void AGenericBoidAI::ForwardTrace(float DeltaTime)
{
	// Initializers 
	FRotator ActorRotation = GetActorRotation();
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.ClearIgnoredActors();

	// 90 Degree angle set Vector for every 10 degrees (-45 left, 45 right, and 10 for every Angle)
	for (int32 Angle = -100; Angle <= 100; Angle += 5)
	{
		// Gets the rotation for the boid 
		FRotator RotatedVector = ActorRotation + FRotator(0, Angle, 0);
		// Defines that the movement vector can only rotate on the yaw axis
		FVector DirectionVector = RotatedVector.Vector();
		// Sets the line-trace slightly in-front of the Boid to not hit-itself
		FVector StartLoc = GetActorLocation() + (GetActorForwardVector() * 70);
		float TraceDistance = 250.f;

		// Where the end of the trace will hit. (Direction Vector so when the boid turns the vector updates)
		FVector Endloc = StartLoc + DirectionVector * TraceDistance;

		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, Endloc, ECC_Camera, TraceParams);
		if (bHit)
		{
			// Calculate the distance to the hit object
			float DistanceToObstacle = (Hit.ImpactPoint - StartLoc).Size();

			// Calculate the box's dimensions & Location
			FVector BoxExtents(10.0f, 10.0f, 10.0f);
			FVector BoxLocation = Endloc;
			
			DrawDebugLine(GetWorld(), StartLoc, Endloc, FColor::Red, false, -1, 0, 4);
			DrawDebugBox(GetWorld(), BoxLocation, BoxExtents, FColor::Orange, false, -1, 0, 4);

			// update the line trace with a new start location or distance
			TurnVector(Angle < 0, DistanceToObstacle);
			break;
		}
	}
}

void AGenericBoidAI::RadiusCohTrace(int32 NumTraces, float RadiusCoh)
{
	// Initializers 
	FVector StartLoc = GetActorLocation() + (GetActorForwardVector() * 50);
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.ClearIgnoredActors();
	TraceParams.AddIgnoredActor(this);
	//int32 CurTrace = 50;
	//float RadiusRange = 200;
	
	// Loops the traces around the body of the boid
	for (int32 i = 0; i < NumTraces; i++)
	{
		// Creates a Circle Angle 
		float Angle = 360.0f * i / NumTraces;
			
	
		// Gets the rotation for the boid 
		FRotator Rotation(0, Angle, 0);
		FVector DirectionVector = Rotation.Vector();
		float TraceDistance = RadiusCoh;

		// Where the end of the trace will hit. (Direction Vector so when the boid turns the vector updates)
		FVector EndLoc = StartLoc + DirectionVector * TraceDistance;
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, EndLoc, ECC_Camera, TraceParams);
		
		// Shows the hit marker
		if (bHit)
		{
			// Calculate the box's dimensions & Location
			FVector BoxExtents(10.0f, 10.0f, 10.0f);
			FVector BoxLocation = EndLoc;
			
			// Draw a persistent debug line
			if (GEngine)
			{
				DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, -1, 0, 2);
				DrawDebugBox(GetWorld(), BoxLocation, BoxExtents, FColor::Blue, false, -1, 0, 4);
				
				while(bHit)
				{
					// Call the weight and input the incoming weight from the other boid 
					//CohWeight();
					break;
				}
			}
		}
	}
}

void AGenericBoidAI::CohWeight(float Weight)
{
	
// check chat

	
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

		// BREAKING ENGINE 
		// Assign New Values 
		//TargetSpeed = NewSpeed;
	} else
	{
		//TargetSpeed = MaxSpeed;
	}
}

void AGenericBoidAI::ForwardMovement(float Speed, float DeltaTime, bool isTurning)
{
	// Where Actor currently is 
	FVector CurrentLocation = GetActorLocation();
	// Destination 
	CurrentLocation += GetActorForwardVector() * Speed * DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), Speed);
	
	// Sets its new location
	SetActorLocation(CurrentLocation);
}



void AGenericBoidAI::Acceleration(float DeltaTime, bool isTurning)
{
}


// Called when the game starts or when spawned
void AGenericBoidAI::BeginPlay()
{ 
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), CurrentWeight);
	
	// Psudeo Code
	BoidArray.AddUnique(this);
	for (AGenericBoidAI* Actor : BoidArray)
	{
		if (Actor && Actor->IsValidLowLevel())
		{
			//BoidWeightMap.Add(Actor, DefaultWeight);
			for (TPair<AGenericBoidAI*, float>& Pair : BoidWeightMap)
			{
				
				UE_LOG(LogTemp, Warning, TEXT("Actor: %s, Weight: %f"), *Actor->GetName(), Weight);
			}



			
		/*else
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor not found in the map."));
		}
			///UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetName());
			// You can print more information about the actor if needed.
		}*/
	}
}

// Called every frame
void AGenericBoidAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ForwardTrace(DeltaTime);
	RadiusCohTrace(50, 250);
	
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



/*void AGenericBoidAI::Seek(FVector Target)
{

	/*FVector DesiredLoc = Target - GetActorLocation();
	DesiredLoc.Normalize();
	DesiredLoc *= MaxSpeed;

	FVector Steer = DesiredLoc - Velocity;

	ApplyForce(Steer);#1#
}

void AGenericBoidAI::ApplyForce(FVector Force)
{
	//Accel += Force;
}*/


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
	