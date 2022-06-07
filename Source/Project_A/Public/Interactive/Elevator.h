// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UPointLightComponent;
class USpotLightComponent;


UCLASS()
class PROJECT_A_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ElevatorMesh;
	UPROPERTY(EditAnywhere)
	float RunSpeed;
	UPROPERTY(EditAnywhere)
	UBoxComponent* OverlapBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interactive")
	USpotLightComponent* ElevatorSpotLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
