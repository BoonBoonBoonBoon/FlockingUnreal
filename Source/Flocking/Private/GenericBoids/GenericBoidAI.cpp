// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/GenericBoidAI.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "GeometryTypes.h"
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

void AGenericBoidAI::TurnVector(bool IsRight)
{
	bIsActiveRotating = true;
	bIsRotatingRight = IsRight;

	StartingRot = GetActorRotation().Yaw;
}

void AGenericBoidAI::ForwardMovement(float Speed, float DeltaTime, bool isTurning)
{
	if (isTurning)
	{
		Speed = 400.f;
	}
	else if (!isTurning)
	{
		Speed = 200.f;
	}
	// Where Actor currently is 
	FVector CurrentLocation = GetActorLocation();
	// adds the forward vector which is multiplied by the speed and the tick
	CurrentLocation += GetActorForwardVector() * Speed * DeltaTime;
	// Sets its new location
	SetActorLocation(CurrentLocation);
}


// Called when the game starts or when spawned
void AGenericBoidAI::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGenericBoidAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForwardTrace(DeltaTime);
	ForwardMovement(NULL, DeltaTime, bShouldTurn);

	// Checks for active rotation.
	if (bIsActiveRotating)
	{
		int Direction = bIsRotatingRight ? 1 : -1;
		AddActorWorldRotation(FRotator(0, Direction * RotationSpeed, 0));
		bIsActiveRotating = GetActorRotation().Yaw - StartingRot > TurnAmount;
	}
}


//////////////////////////////////
///
///
///
////*void AGenericBoidAI::CheckRotation(int32 Angle, float DeltaTime, bool bHit)
//{
	// If traces fire off on left actor turns right , add separate bool
	/*if (TurnProgress < 1.f)
	{
		for (; Angle < 0; RightTurnRate++)
		{
			//bShouldTurn = true;
			RightVectorMovement(bHit, DeltaTime, RightTurnRate);

			if (RightTurnRate == 180)
			{
				//TurnProgress = 0;

				// Go to new function which resets turn rate and turn progress to make it able to loop
				
				
				return;
			}
		}
	}#1#
}*/


	/*void AGenericBoidAI::RightVectorMovement(bool bTraceHit, float DeltaTime, int32 TurnRate)
{
	// Log the parameters using UE_LOG
	//UE_LOG(LogTemp, Warning, TEXT("bTraceHit: %s, DeltaTime: %f, TurnRate: %d"), bTraceHit ? TEXT("True") : TEXT("False"), DeltaTime, TurnRate);
	/*
	if(bTraceHit)
	{
		const FRotator RightRotation = FRotator(0, TurnRate, 0);
		
		TurnProgress += DeltaTime / RotationDelay;
		UE_LOG(LogTemp, Warning, TEXT("TurnProg: %f "), TurnProgress);
		UE_LOG(LogTemp, Warning, TEXT("RotationDelay: %f "), RotationDelay);
		
		TurnProgress = FMath::Clamp(TurnProgress, 0.f, 1.f);
		UE_LOG(LogTemp, Warning, TEXT("TurnProg After Clamp: %f "), TurnProgress);
		
		// Interpolate the rotation smoothly using Lerp
		const FRotator NewRotation = FMath::Lerp(NewRotation, RightRotation, TurnProgress);
		SetActorRotation(NewRotation);
		
		//UE_LOG(LogTemp, Warning, TEXT("New Rotation: %s"), *NewRotation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("RightRotation: %s"), *RightRotation.ToString());
	}#1#
}*/