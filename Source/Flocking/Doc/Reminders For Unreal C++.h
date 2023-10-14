#pragma once

						// Doccumentation File 
						
						// Full of previous examples and explanations.




	/** Casting -
	* 
	* To Cast, 
	* Inside the class of your choice. For Example a pickup class.
	* 
	* You want the pickup class to access ALL of the data inside the class you want to cast. For Example your player class.
	* 
	* To do so, you create a pointer of the class you want casting.
	* You then use CAST with the class in the template.
	* 
	* I used gameplaystatistics as a arugment (@see GameplayStatics.)
	* Used a function of the class. 
	* Check if its spawned in - Player index.
	* 
	*	
	* Unreal Doc -
	* 
	* A common communication method where you take a 
	* refrence to an actor and try to convert it to 
	* a different class
	* 
	* 
	* Notes -
	* 
	* <T> Is the class you are casting too.
	* (Var) Is the variable you want casted.
	* 
	* So Player = Cast<ClassWeCastToo>(ClassObject)
	* 
	* Make Sure its valid before (Not NullPtr) to avoid crashes.
	* 
	* You can then Access the Object:
	* Player->ObjectWeWant;
	* 
	* Casts is <From>(TO)
	*/

	PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	


	/** Delegates -
	* To use a delegate we firstly need to define it as a UFUNCTION in the header.
	* This is so it can communicate to the blueprints. (Not Yet)
	* 
	* A delegate is an event, that we can Define, Call or respond to.
	*/
	Trigger->OnComponentBeginOverlap.AddDynamic(Param1, param2);
	/** Delegates -
	* Trigger is the object we want to be able to interact with another.
	* OnCompBegin is the name of the delegate we want to use (Theres a few).
	* 
	* AddDynamic is the binding.
	* 
	* The Parameters are:
	* 1. UserObject - this is the parameter thats calling the object, in this case us. (this, param1)
	* 2. FunctionName - this needs the name of the function, determines which function to call when delegate fires.
	* it needs a address and a class specified (this, &ACasted::FunctionName)
	* 
	* -
	* 
	* Param1 Represents a class, which will be used to compare it with (Param 2) - represents the objects class.
	* Cast<Param1>(Param2)
	* 
	* param 2 youll need an object which you can copy from the Beginoverlap parameters (AActor* OtherActor)
	* 
	* #include "APlayerCharacter.h"
	* Cast<APlayerCharacter>(OtherActor)
	* 
	* To check if it worked you need to use a if statement.
	* 
	* if(Cast<APlayercharacter>(OtherActor)){}
	* 
	* 
	/**
	* Set pointer of AActor Class,GetOwner is Method of actorcomp
	* if owner is true. Access OTAD event, use dynamic delegate to bind event and function
	* tell computer to look at TakeDamage function
	* @see takedamage
	

	// Get reference to owning actor,
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		// Valid owner returned, whenever takedamage function called, add dynamic binding. 
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::OnTakeDamage);
	}
	*/




	/**	Spawning an Actor -
	*
	* Use UWorld::SpawnActor()
	* # include "Enginge/World.h"
	*
	* Access Variables and functions of a specific class.
	* 
	* To Spawn an actor need to get the UWorld since we will need to generate something inside it.
	* Assign a prt to UWorld to store the object, then Getworld to return the UWorld object.
	* 
	* Now we have a way to tell the function we want it in the game world we need to tell it to spawn.
	* Use UWorld::SpawnActor function (Takes 3 Params. Uclass, Flocation, FRotation)
	* UClass (Actor we want to Spawn)
	* FLocation (X,Y,Z) - Needs the address &
	* FRotation (Pitch, Roll, Yaw) - Needs the address &
	* 
	* To Get the Actor class we want to spawn we need to use TSubclassOf<>
	* TSubClass allows us to refrences classes Ex <AActor> will give a large list of child A. 
	* 
	* GetDefaultObject()
	* 
	*/
	TSubclassOf<AActor> ActorPointer;


	/** LineTraces - 
	* 
	* Used to test collision, can test for visuals (ECC_Visibility) or can test on objects (Pawns, Actors).
	* Defined in UWorld return the first hit object back
	* 
	* Firstly, Need to define a Hit result variable as it will need to be able to get the objects data it hit.
	* Need Fvector to use it to get the X,Y,Z values of the start location. In this case the actors root component, can change with sockets on a weapon.
	* Without FVector Forward we dont have a way to tell the line trace what direction to go and it will just go nowhere.
	* End location gets the forwardvector vector times it by the UE Cm's we then add the start location to define point a to point b
	* Fcollision is a struct that just checks collision.
	* We get world to refrence the level we want the trace to spawn in, we then access the Linetrace function through it since its a UWorld object.
	* we assign it to bHit since we want to run it through an if statement to check if it has been hit we can print a drawdebugbox
	* drawdebug numbers determine longevity and thickness of trace.
	* we do FHit.impactpoint because we want to access the struct variables inside the FHitResult.
	* 
	* 
	* First Trial -
	FHitResult FHit;
	FVector StartLoc = GetActorLocation();
	FVector EndLoc(0,0,100.f);
	GetWorld()->LineTraceSingleByChannel(FHit, StartLoc, EndLoc, ECC_Visibility);
	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red);
	* 
	* Second Trial -
	FHitResult FHit;
	FVector StartLoc = GetActorLocation();
	FVector ForwardVector = CameraComp->GetForwardVector();
	FVector EndLoc((ForwardVector * 2500.f) + StartLoc);
	FCollisionQueryParams CollisionParam;
	bool bHit = GetWorld()->LineTraceSingleByChannel(FHit, StartLoc, EndLoc, ECC_Visibility, CollisionParam);
	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red,false, 2, 0, 3);
	* 
	* if (bHit)	
	{
	DrawDebugSphere(GetWorld(),FHit.ImpactPoint, 20, 5, FColor::Green, false, 2, 0, 3);
	}
	* 
	* 
	*/

	//AProjectileBase* ProjectileActor;

	//if (BulletPtr != nullptr) {

		//BulletPtr = GetWorld()

	//}

	/**
	Want to spawn actor -
	to spawn actor we need to give it a location to spawn.
	could use getworld maybe or a body part of the actor.

	onactorhit destroy
	FHitResult

	https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Actors/Spawning/
	*/

	/**
	* @See Health
	* On TakeDamage Health is given the data,
	* FMath which is a struct for math problems.
	*
	* Use :: because in the class mathUtility FMath is a object like Clamp. Used to refrence object.
	*
	* @See Clamp
	* Uses Clamp method, it requires float and something to attach it to a double.
	*
	* Want to tell health to give its original health then minus the incoming damage float,
	* this tells health that we are getting the value of the health.
	* Clamp needs a minimum vaue and a maximum value
	* give it 0.0f, health wont go below 0.
	* give health back again since that will be the maximum value.
	*
	* Use if to check if the damage data has gone above 0.
	* if true it returns to functon TD,
	* Then minus it from health.
	*/


	if (Damage <= 0)
	{
		return;		// ... Checking if take damage. 
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);


	/**	Zooming
	* 
	* Focusing in and out is simple. 
	* change the FOV of the character. 
	* 
	* Firstly you want to get whatever the characters using as a camera. this camera will have a set FOV which you can access, alter it however you want.
	* 
	* for extra credit if you want the camera to slow the movement speed, make a method dedicated to checking if the arguments are true or not and can be exectued.
	* also make sure its checking every tick since sometimes a input key is pressed, it will prioity stack management and movement speed be overriden. 
	*/
		CameraComp->SetFieldOfView(70.f);
		CheckBooleans(bIsWalking, bIsRunning, bIsCrouched, bIsFiring, bIsZoomedin == true);
		
	/** Enumerators / Enums
	* Is a user defined data type consists of int constants. KeyWord enum.
	* by default int are layed out like index
	* enum season {Spring, Summer, Autum, Winter};
	* 0,1,2,3;
	*
	* Can change number during declaration.
	*
	*/

	/**	This Keyword
	*
	*	Only Accessable through a member function
	*	A Memeber Function is just a declared memeber of a class. (Think of APlayerCharacter, Now you look in the header and there are visibility modes - Private, Public. if you delcare it in one of those
		it becomes a member of that class and can access other members of the class i.e. variables/functions. if not delcared in one of the modes need to use a scope operator ::)
	*	i.e a member function is a function inside a class.
	* 
	* This is a pointer, whenever you use the keyword this it stores the address of the current object. 
	* 
	* so for example we have a Socket which is of class USocket and it has a APlayer Pointer assinged.
	* We get the socket, which has all this infomation inside of it, and call the function AttachActor.
	* AttachActor (AActor* Actor, class USkeletalMeshComponent* SkelComp).
	* The this is in place of the actor pointer, so we are telling the function we want to attach this to the socket.
	* The SkelComp is the skeletelmesh component associated with the socket.
	* 
	* pointer to the current object instance that the method belogs to.
	* What i gather is when we say this we are refering to the actual base class 
	* 
	* in conclusion
	* We want to attach this()actor to the socket and the socket we want to attach to is the RifleHandSocket.
	* -----
	* const USkeletalMeshSocket* Socket = PlayerRefrence->GetMesh()->GetSocketByName("RifleHandSocket");
	* Socket->AttachActor(this, PlayerRefrence->GetMesh());
	* 
	*/

	/** TArrays
	*	Is a dynamic array which means it choses to allocate extra space in the memory just incase we go over the set amount 
	*	of memory addresses, and can keep expanding if need be.
	* 
	*	It works the same as a normal array. You can add elements to the front or back, take away elements see how many elements
	*	are in the array and so on.
	* 
	*	.Num() Returns the value of how many elements in the array
	*	.Add adds a element to the end of an array
	*	.AddUnique adds a element to the end of an array, however, it will not allow a duplicate of the same item.
	*
	*
	*/


	/** ForceInLine
	* ForceInline is a inline call
	* inline call is basically when you call a function inside a function. Unlike a normal function though, it does not change the control flow (Jumping between function groups)
	* instead the inline function will tend to be called and copied inside the function we are calling. The code inside the inline will be very very basic
	* like a call or a return.
	* inline lets the compiler chose if it wants to do the function or not.
	* forceInline forces the compiler to do it. 
	* 
	*/


	/** Interfaces -
	* 
	* 
	* 
	* 
	* 
	* 
	*/


	/** Timers -
	* 
	* Use Unreals Timerhandle to define the timer. FTimerHandle (Specifcer);
	* 
	* Then if we want to call the timer all we do is 
	* GetWorld()/ Since we are calling it in the level
	* GetWorld()->GetTimerManager / returns the manager for handling timers
	* .SetTimer / Tells the timerManager what to do.
	* ((FTimerHandle name)) and so on.
	* 
	*/



	/** UGameplaystatistics -
	* 
	* #include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
	* 
	* Gameplay utlity functions for cpp and Bp
	* 
	*/