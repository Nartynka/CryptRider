// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if(PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
 	// DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);
	// DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, 
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2, 
		CollisionSphere
	);

	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Physics Handle is null!!!!!!!!!!!!!!!!!!!!!!!!!"));

	return PhysicsHandle;
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle==nullptr)
		return;
	if(PhysicsHandle->GetGrabbedComponent() != nullptr)
		PhysicsHandle->ReleaseComponent();
}