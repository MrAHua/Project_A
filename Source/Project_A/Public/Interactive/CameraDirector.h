// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT()
struct FCameraInfo{

	GENERATED_BODY ()

	UPROPERTY(EditAnywhere)
	AActor* Camera;
	UPROPERTY(EditAnywhere)
	float CameraWaitTime;
	UPROPERTY(EditAnywhere)
	float SmoothBlendTime;

	int CameraIndex;
};

UCLASS()
class PROJECT_A_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<FCameraInfo> CameraInfos;
	
	float TimeToNextCameraChage;
	float CameraWaitTime;
	float SmoothBlendTime;
	float CostTime;
	int CameraIndex;
	bool CanSetNextCamera;
};
