// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOKINGUY_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere)
		float grabDistance = 400;
	UPROPERTY(EditAnywhere)
		float grabRadius = 200;
	UPROPERTY(EditAnywhere)
		float holdDistance = 30;


	UFUNCTION(BlueprintCallable)
	void ReleaseObject();
	UFUNCTION(BlueprintCallable)
	UPhysicsHandleComponent* GetPhysicsHandle() const;
	UFUNCTION(BlueprintCallable)
	void GrabObject();
};
