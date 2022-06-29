// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CanSetNextCamera = true;
	BlendCountDownTime = -1.0f;
	StartCameraTiming = true;
	StartBlendTiming = false;
	IsCycle = true;

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

	if (IsCycle && CameraInfos.Num() > 0)
	{
		if (CanSetNextCamera)
		{
			//停留时间
			CameraWaitTime =CameraInfos[CameraIndex].CameraWaitTime;
			//滑动时间
			BlendCountDownTime = CameraInfos[CameraIndex].SmoothBlendTime;

			CanSetNextCamera = false;
		}
		//相机等待计时
		if (StartCameraTiming)
		{
			CameraWaitTime = CameraWaitTime - DeltaTime;
// 			FString CameraWaitTimeS = FString::SanitizeFloat(CameraWaitTime);
// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *CameraWaitTimeS);
		}
		//相机滑动计时
		if (StartBlendTiming)
		{
			BlendCountDownTime = BlendCountDownTime - DeltaTime;
// 			FString BlendCountDownTimeS = FString::SanitizeFloat(BlendCountDownTime);
// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *BlendCountDownTimeS);
			//滑动结束之后设置下一个相机信息
			if (BlendCountDownTime <= 0)
			{
				CameraIndex++;
				CanSetNextCamera = true;
				StartBlendTiming = false;//关闭滑动倒计时
				StartCameraTiming = true;//开启相机等待倒计时
				
				//停留时间>0,组织当前帧进入下边逻辑
				CameraWaitTime = 1.0f;
			}
		}
		
		//相机等待计时完成&&相机没有滑动
		if (CameraWaitTime <= 0.0f && !StartBlendTiming)
		{
			APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (OurPlayerController)
			{
				//最后一个相机
				if (CameraIndex >= CameraInfos.Num() - 1)
				{
					//最后一个相机后滑动到角色相机
					//OurPlayerController->SetViewTargetWithBlend(OurPlayerController->GetPawn(), CameraInfos[CameraIndex].SmoothBlendTime);
					//IsCycle = false; //Stop camera cycle moving when it turn to the last camera
					//最后一个相机后滑动初始相机
					CameraIndex = 0;
					OurPlayerController->SetViewTargetWithBlend(CameraInfos[CameraIndex].Camera, CameraInfos[CameraInfos.Num() - 1].SmoothBlendTime);
					StartCameraTiming = false;//关闭相机等待计时
					BlendCountDownTime = CameraInfos[CameraInfos.Num() - 1].SmoothBlendTime;
					StartBlendTiming = true;//开启滑动计时
				}
				else 
				{
					//读取下一个相机
					if ((OurPlayerController->GetViewTarget() != nullptr) && (CameraInfos[CameraIndex + 1].Camera != nullptr))
					{
// 						FString index = FString::FromInt(CameraIndex);
// 						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Camera[%s]----start"), *index), true);
						OurPlayerController->SetViewTargetWithBlend(CameraInfos[CameraIndex + 1].Camera, CameraInfos[CameraIndex].SmoothBlendTime);
						StartCameraTiming = false;//关闭相机等待计时
						BlendCountDownTime = CameraInfos[CameraIndex].SmoothBlendTime;
						StartBlendTiming = true;//开启滑动计时
					}
				}
			}
		}
	}
}

