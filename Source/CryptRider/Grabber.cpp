// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
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

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	PhysicsHandle = nullptr;
	if(PhysicsHandle != nullptr){
		UE_LOG(LogTemp, Display, TEXT("Name: %s"), *PhysicsHandle->GetName());}
	else
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle is null!!!!!!!!!!!!!!!!!!!!!!!!!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGrabber::Grab()
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
 	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);
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
		AActor* HitedActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit object: %s"), *HitedActor->GetActorNameOrLabel());
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Magenta, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Emerald, false, 5);
	}
	else
		UE_LOG(LogTemp, Display, TEXT("No actor hit"));
}
