// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue5_fps_boxPickUpComponent.h"

Uue5_fps_boxPickUpComponent::Uue5_fps_boxPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void Uue5_fps_boxPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &Uue5_fps_boxPickUpComponent::OnSphereBeginOverlap);
}

void Uue5_fps_boxPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	Aue5_fps_boxCharacter* Character = Cast<Aue5_fps_boxCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
