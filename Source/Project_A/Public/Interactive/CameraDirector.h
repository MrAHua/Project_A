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

	UPROPERTY(EditAnywhere, Category = "Camera Director")
		TArray<FCameraInfo> CameraInfos;


	/* 相机等待时间*/
	float CameraWaitTime;
	/* 相机滑动时间倒计时 */
	float BlendCountDownTime;
	int CameraIndex;
	bool CanSetNextCamera;
	/* Whether open camera wait ticking*/
	bool StartCameraTiming;
	/* Whether open blend view target ticking*/
	bool StartBlendTiming;
	/* 是否循环相机 */ 
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Camera Director")
	bool IsCycle;
};
