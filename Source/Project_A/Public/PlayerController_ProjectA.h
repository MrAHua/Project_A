// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_ProjectA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API APlayerController_ProjectA : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
};
