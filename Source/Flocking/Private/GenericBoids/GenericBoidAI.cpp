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

		Head=CreateDefaultSubobject<USphereComponent>("HeadComp");
    	Head->SetupAttachment(RootComponent);
    
    	HeadShape=CreateDefaultSubobject<UStaticMeshComponent>("HeadShape");
    	HeadShape->SetupAttachment(Head);
}

int bIsCurrentlyRotating;
// Creates Peripheral Vision
void AGenericBoidAI::ForwardTrace(float DeltaTime)
{
	// Get Actors Current rotation
	FRotator ActorRotation = GetActorRotation();

	// 90 Degree angle set Vector for every 10 degrees (-45 being left, 45 being right, and 10 being for every sector)
	// Could use for cohesion and others too and set to 360 degrees 
	for (int32 Angle = -45; Angle <= 45; Angle += 10)
	{
		// Set the Vector rotation (Yaw) 
		//FVector DirectionVector = FRotationMatrix(FRotator(0, Angle, 0)).GetUnitAxis(EAxis::X);

		FRotator RotatedVector = ActorRotation + FRotator(0, Angle, 0);
		FVector DirectionVector = RotatedVector.Vector();
	
		FHitResult Hit;
		FVector StartLoc = GetActorLocation();
		constexpr float TraceDistance = 450.f;
		const FCollisionQueryParams TraceParams;

		FVector Endloc = StartLoc + DirectionVector * TraceDistance;

		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, Endloc, ECC_Visibility, TraceParams);
		if (bHit)
		{
			DrawDebugLine(GetWorld(), StartLoc, Endloc, FColor::Red, false, -1, 0, 4);
			CheckRotation(Angle, DeltaTime, bHit);
		}
	}
}

void AGenericBoidAI::CheckRotation(int32 Angle, float DeltaTime, bool bHit)
{
	// If traces fire off on left actor turns right , add separate bool
	if (TurnProgress < 1.f)
	{
		for (; Angle < 0; RightTurnRate++)
		{
			//bShouldTurn = true;
			RightVectorMovement(bHit, DeltaTime, RightTurnRate);

			if (RightTurnRate == 180)
			{
				TurnProgress = 0;

				// Go to new function which resets turn rate and turn progress to make it able to loop
				
				
				return;
			}
		}
	}
}

// This whole function is made to check if we are rotating,
// if rotation is below 1 then we continue and return false 
// if rotation is above 1 we return true


void AGenericBoidAI::ForwardMovement(float Speed, float DeltaTime, bool isTurning)
{
	if(isTurning)
	{
		Speed = 400.f;
	}
	else if(!isTurning)
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

void AGenericBoidAI::RightVectorMovement(bool bTraceHit, float DeltaTime, int32 TurnRate)
{
	// Log the parameters using UE_LOG
	//UE_LOG(LogTemp, Warning, TEXT("bTraceHit: %s, DeltaTime: %f, TurnRate: %d"), bTraceHit ? TEXT("True") : TEXT("False"), DeltaTime, TurnRate);
	
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
	}
}

void AGenericBoidAI::LeftVectorMovement(bool bTraceHit, float DeltaTime, int32 TurnRate)
{
	if(bTraceHit)
	{

		
	}
}

// Called when the game starts or when spawned
void AGenericBoidAI::BeginPlay()
{
	Super::BeginPlay();
}

void AGenericBoidAI::DelayedRotation()
{
	/*UE_LOG(LogTemp, Warning, TEXT("TurnRate: %d"), RightTurnRate);
	// Once hit maximum turn rate return
	if (RightTurnRate == 90)
	{
		GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);
		return;
	}*/
}

// Called every frame
void AGenericBoidAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForwardTrace(DeltaTime);
	ForwardMovement(NULL, DeltaTime, bShouldTurn);
}


//UE_LOG(LogTemp, Warning, TEXT("Angle: %d - Hit Actor: %s"), Angle, *Hit.GetActor()->GetName());
//UE_LOG(LogTemp, Warning, TEXT("Angle: %d - Turning Degrees : %d"), Angle, RightTurnRate);

//FCollisionParameters::AddIgnoreActor(); Ignore Actor type
		
/*if(rayCast==true) foundWall=true
if(foundWall==true){
	//Run our lerp
	if(lerpProgress==1){
		foundWall=false;
	
		}*/

/*// If traces fire off on right actor turns left
		for (; Angle > 0; LeftTurnRate++)
		{
			const FRotator LeftRotation = FRotator(0, LeftTurnRate, 0);
			SetActorRotation(LeftRotation);
			UE_LOG(LogTemp, Warning, TEXT("Angle: %d - Turning Degrees : %d"), Angle, RightTurnRate);

			// Once hit maximum turn rate return
			if (RightTurnRate == 90)
			{
				return;
			}
		}*/

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