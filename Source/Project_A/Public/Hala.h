// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Chapter4_ActorsandComponents/InventoryComponent.h"
#include "Chapter4_ActorsandComponents/InventoryActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Hala.generated.h"

UCLASS()
class PROJECT_A_API AHala : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHala();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		UInventoryComponent* MyInventory;
	UPROPERTY()
		UCameraComponent* MainCamera;
	UFUNCTION()
		void DropItem();
	UFUNCTION()
		void TakeItem(AInventoryActor* InventoryItem);
	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, 
			bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);

private:
	FVector MovementInput;
	FVector CameraInput;
};
