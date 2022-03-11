// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Weapen.h"
#include "GameMode_ProjectA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API AGameMode_ProjectA : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UClassNames)
		TSubclassOf<UWeapen> UWeapen;

public:
	void initGameState();
};
