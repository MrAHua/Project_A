// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Elevator.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UPointLightComponent;
class USpotLightComponent;

UENUM()
enum class EElevatorState:uint8
{
	Stop = 0,
	Running
};

UCLASS()
class PROJECT_A_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
		USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ElevatorMesh;
	UPROPERTY(EditAnywhere)
		float RunSpeed;
	UPROPERTY(EditAnywhere)
		UBoxComponent* OverlapBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interactive")
		USpotLightComponent* ElevatorSpotLight;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> widgetBlackLines;

	UUserWidget* widgetBlackLinesInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void MoveToTargetFloor(const FVector& TargetFloorLocation);
};
