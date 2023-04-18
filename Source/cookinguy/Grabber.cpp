// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsCollisionHandler.h"
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

	// ...

	
	
}
#define ECC_Grab ECC_GameTraceChannel1

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if(physicsHandle == nullptr)
	{
		return;
	}

	if(physicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
}



UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber needs PhysicsHandle"));
	}
	return result;
}
void UGrabber::ReleaseObject()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if(physicsHandle == nullptr)
	{
		return;
	}

	if(physicsHandle->GetGrabbedComponent() != nullptr)
	{
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		physicsHandle->ReleaseComponent();
	}
		
	
}
void UGrabber::GrabObject()
{
	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr)
	{
		return;
	}
	
	FVector lineStart = GetComponentLocation();
	FVector lineEnd = lineStart + GetForwardVector() * grabDistance;
	DrawDebugLine(GetWorld(), lineStart, lineEnd, FColor::Cyan);

	FCollisionShape grabSphere = FCollisionShape::MakeSphere(grabRadius);
	FHitResult hitResult;
	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		lineStart, lineEnd,
		FQuat::Identity,
		ECC_Grab,
		grabSphere
		);

	
	if(hasHit)
	{
		AActor* hitActor = hitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *hitActor->GetActorNameOrLabel());

		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->WakeAllRigidBodies();

		physicsHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			hitResult.GetComponent()->GetComponentRotation()
			);
	}
	

}

