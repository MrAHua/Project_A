// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CanSetNextCamera = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	/*int ArrayNum = CameraInfos.Num();
	FString ArrayNumStr = FString::FromInt(ArrayNum);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("find cameras in scene>>"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *ArrayNumStr );*/

	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (OurPlayerController)
	{
		if (CameraInfos.Num() > 0)
		{
			OurPlayerController->SetViewTarget(CameraInfos[CameraIndex].Camera);
		}
	}
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CameraInfos.Num() > 0)
	{
		if (CanSetNextCamera)
		{
			//停留时间
			CameraWaitTime =CameraInfos[CameraIndex].CameraWaitTime;
			//滑动时间
			SmoothBlendTime = CameraInfos[CameraIndex].SmoothBlendTime;
			//停留时间+滑动时间
			CostTime = CameraWaitTime + SmoothBlendTime;
			CanSetNextCamera = false;
		}

		TimeToNextCameraChage = CameraWaitTime - DeltaTime;
		CameraWaitTime = TimeToNextCameraChage;
		FString CameraWaitTimeS = FString::SanitizeFloat(CameraWaitTime);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,*CameraWaitTimeS);
		//停留时间消耗完成后
		if (TimeToNextCameraChage <= 0.0f)
		{
			//CanSetNextCamera = true;
			APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (OurPlayerController)
			{
				if (CameraIndex >= CameraInfos.Num() - 1)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Reset"));
					FString index = FString::FromInt(CameraIndex);
					UE_LOG(LogTemp, Warning, TEXT("Camera[%s]----start"), *index);
					CameraIndex = 0;
					OurPlayerController->SetViewTargetWithBlend(CameraInfos[CameraIndex].Camera, CameraInfos[CameraInfos.Num() - 1].SmoothBlendTime);
					CanSetNextCamera = true;
				}
				else {
					//读取下一个相机
					if ((OurPlayerController->GetViewTarget() != nullptr) && (CameraInfos[CameraIndex + 1].Camera != nullptr))
					{
						FString index = FString::FromInt(CameraIndex);
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Camera[%s]----start"), *index), true);
						OurPlayerController->SetViewTargetWithBlend(CameraInfos[CameraIndex + 1].Camera, CameraInfos[CameraIndex].SmoothBlendTime);
						CameraWaitTime += CameraInfos[CameraIndex].SmoothBlendTime;
						if (CameraWaitTime > 0)
						{
							CanSetNextCamera = false;
						} 
						else
						{
							CanSetNextCamera = true;
							CameraIndex++;
						}
					}
				}
			}
		}
	}
}

