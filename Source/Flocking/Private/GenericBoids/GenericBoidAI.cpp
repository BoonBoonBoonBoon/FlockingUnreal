// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/GenericBoidAI.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
AGenericBoidAI::AGenericBoidAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		Head=CreateDefaultSubobject<USphereComponent>("HeadComp");
    	Head->SetupAttachment(RootComponent);
    
    	HeadShape=CreateDefaultSubobject<UStaticMeshComponent>("HeadShape");
    	HeadShape->SetupAttachment(Head);
}

// Peripheral Vision
void AGenericBoidAI::ForwardTrace()
{
	// 90 Degree angle set Vector for every 10 degrees (-45 being left, 45 being right, and 10 being for every sector)
	// Could use for cohesion and others too and set to 360 degrees 
	for(int32 Angle = -45; Angle <= 45; Angle += 10)
	{
		// Set the Vector rotation (Yaw) 
		FVector DirectionVector = FRotationMatrix(FRotator(0, Angle, 0)).GetUnitAxis(EAxis::X);
		// Return Hit
		FHitResult Hit;
		// Start Location of trace
		FVector StartLoc = GetActorLocation();
		// Trace Distance
		const float TraceDistance = 600.f;
		// Trace Params
		const FCollisionQueryParams TraceParams;
	
		FVector Endloc = StartLoc + DirectionVector * TraceDistance;
			
		//FCollisionParameters::AddIgnoreActor(); Ignore Actor type
			
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, Endloc,
		ECC_Visibility, TraceParams);
		if(bHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Angle: %d - Hit Actor: %s"), Angle, *Hit.GetActor()->GetName());
				
			DrawDebugLine(GetWorld(), StartLoc, Endloc,
			FColor::Red, false, -1, 0, 4);
				
			while(Angle <= 10)
			{
				// Log the value of PerTrace
				//UE_LOG(LogTemp, Warning, TEXT("PerTrace: %d"), PerTrace);
					
				RightVectorMovement(bHit, NULL);
				//FPlatformProcess::Sleep(0.1f);
			}
		}
	}
}

void AGenericBoidAI::ForwardMovement(float Speed, float DeltaTime, bool isTurning)
{
	
		Speed = 400.f;
		// Where Actor currently is 
		FVector CurrentLocation = GetActorLocation();
		// adds the forward vector which is multiplied by the speed and the tick
		CurrentLocation += GetActorForwardVector() * Speed * DeltaTime;
		// Sets its new location
		SetActorLocation(CurrentLocation);
	
}

void AGenericBoidAI::RightVectorMovement(bool bTraceHit, float Tick)
{
	if(bTraceHit)
	{
			// Rotate The Actor 10 Degrees
			const FRotator RotateRightVector = FRotator(0, 10, 0);
			SetActorRotation(RotateRightVector);
	} else
	{
		return;
	}
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

	ForwardTrace();
	ForwardMovement(NULL, DeltaTime, NULL);
	//RightVectorMovement(NULL, DeltaTime);
}





// Define the starting angle
//int32 Angle = -45;
// Continuously rotate while the line trace hits something
/*while (true)
{
	// Set the Vector rotation (Yaw) 
	FVector DirectionVector = FRotationMatrix(FRotator(0, Angle, 0)).GetUnitAxis(EAxis::X);
	// Start Location of trace
	FVector StartLoc = GetActorLocation();
	// Trace Distance
	const float TraceDistance = 600.f;
	// Trace Params
	FCollisionQueryParams TraceParams;

	FVector Endloc = StartLoc + DirectionVector * TraceDistance;
    
	// Perform the line trace
	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, Endloc, ECC_Visibility, TraceParams);
    
	// Log the trace results
	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Angle: %d - Hit Actor: %s"), Angle, *Hit.GetActor()->GetName());
        
		// Rotate the actor by 10 degrees
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += 10;
		SetActorRotation(NewRotation);
	}
	else
	{
		// Trace was unsuccessful, break out of the loop
		break;
	}
    
	// Increment the angle for the next trace
	Angle += 10;
}*/