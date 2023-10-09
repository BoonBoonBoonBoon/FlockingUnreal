// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBoids/GenericBoidAI.h"
#include "DrawDebugHelpers.h"
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

void AGenericBoidAI::ForwardTrace()
{
	
	// Out Hit 
	FHitResult HitResult;
	// Start Location
	FVector ActorLocation = GetActorLocation();
	// End of Trace
	FVector EndLocation = GetActorLocation()+=GetActorForwardVector()+=FVector(500,0,0);
	// Object we are looking for
	FCollisionQueryParams QueryParams;
	
	bool Trace = GetWorld()->LineTraceSingleByChannel(HitResult, ActorLocation, EndLocation, ECC_Visibility, QueryParams);
	if(Trace)
	{
		DrawDebugLine(GetWorld(), ActorLocation, EndLocation, FColor::Red, false, -1, 1, 6);
		if(HitResult.bBlockingHit)
		{
			// Draw multiple lines within the pheriphral range
			// Make the hit change the velcity and angle of the actor
			//GetActorRightVector();
			
			// Takes two vector and boolean
			//UKismetMathLibrary::SelectVector();

			
		}
		else
		{
			
		}
	}
}

void AGenericBoidAI::ForwardMovement(float Speed, float DeltaTime)
{
		Speed = 400.f;
		// Where Actor currently is 
		FVector CurrentLocation = GetActorLocation();
		// adds the forward vector which is multiplied by the speed and the tick
		CurrentLocation += GetActorForwardVector() * Speed * DeltaTime;
		// Sets its new location
		SetActorLocation(CurrentLocation);
}

void AGenericBoidAI::TurnMovement()
{
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
	ForwardMovement(NULL, DeltaTime);
}

