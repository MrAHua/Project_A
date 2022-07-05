// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateBase_ProjectA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API AGameStateBase_ProjectA : public AGameStateBase
{
	GENERATED_BODY()
public:
		AGameStateBase_ProjectA();

public:


	UFUNCTION()
		void SetScore(int32 NewScore);
	UFUNCTION()
		int32 GetScore();
	//virtual void BeginPlay() override;
private:
	UPROPERTY()
		int32 CurrentScore;
};
