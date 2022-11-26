// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "GameFramework/Actor.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

   AActor* AcctableActor = GetAcctableActor();
   if(AcctableActor != nullptr)
   {
      UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(AcctableActor->GetRootComponent());
      if(Component!=nullptr)
      {
         Component->SetSimulatePhysics(false);
         Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
      }
      if(Mover!=nullptr)
         Mover->SetShouldMove(true);
   }
   else
      if(Mover!=nullptr)
         Mover->SetShouldMove(false);
}

AActor* UTriggerComponent::GetAcctableActor() const
{
   TArray<AActor*> Actors;
   GetOverlappingActors(Actors);

   for(AActor* Actor : Actors)
   {
      if(Actor->ActorHasTag(ActorTag))
      {
         return Actor;
      }
   }
   return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
   Mover = NewMover;
}