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
	int ArrayNum = CameraList.Num();
	FString ArrayNumStr = FString::FromInt(ArrayNum);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *ArrayNumStr );
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;
	TimeToNextCameraChage -= DeltaTime;//-0.016,1.968
	FString FloatValue = FString::SanitizeFloat(TimeToNextCameraChage);
	
	if (TimeToNextCameraChage <= 0.0f	)
	{
		TimeToNextCameraChage += TimeBetweenCameraChanges;//1.984
		FString FloatValue2 = FString::SanitizeFloat(TimeToNextCameraChage);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *FloatValue2);
		CameraIndex++;
		FString CameraIndexValue = FString::FromInt(CameraIndex);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *CameraIndexValue);
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController && CameraList.Num()>0)
		{
			if (CameraIndex >= CameraList.Num())
			{
				CameraIndex = 0;
			}
			if ((OurPlayerController->GetViewTarget() != nullptr) &&(CameraList[CameraIndex] != nullptr) )
			{
				OurPlayerController->SetViewTargetWithBlend(CameraList[CameraIndex], SmoothBlendTime);
			}
			//else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			//{
			//	//平滑地混合到摄像机2。
			//	OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			//}
		}
	}
}

