// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	int ArrayNum = CameraInfos.Num();
	FString ArrayNumStr = FString::FromInt(ArrayNum);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("find cameras in scene>>"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *ArrayNumStr );
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//下一个相机等待时间
	float TimeBetweenCameraChanges =CameraInfos[CameraIndex].TimeBetweenCameraChanges;
	//滑动时间
	float SmoothBlendTime = CameraInfos[CameraIndex].SmoothBlendTime;
	TimeToNextCameraChage -= DeltaTime;
	FString FloatValue = FString::SanitizeFloat(TimeToNextCameraChage);
	
	if (TimeToNextCameraChage <= 0.0f	)
	{
		TimeToNextCameraChage += TimeBetweenCameraChanges;
		CameraIndex++;
		FString CameraIndexValue = FString::FromInt(CameraIndex);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *CameraIndexValue);

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController && CameraInfos.Num()>0)
		{
			if (CameraIndex >= CameraInfos.Num())
			{
				CameraIndex = 0;
			}
			if ((OurPlayerController->GetViewTarget() != nullptr) &&(CameraInfos[CameraIndex].Camera != nullptr) )
			{
				OurPlayerController->SetViewTargetWithBlend(CameraInfos[CameraIndex].Camera, SmoothBlendTime);
			}
		}

	}
}

