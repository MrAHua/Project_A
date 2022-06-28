// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_ProjectA.h"
#include "GameFramework/PlayerController.h"

void APlayerController_ProjectA::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
