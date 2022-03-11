// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_ProjectA.h"

void AGameMode_ProjectA::initGameState() {
	AGameMode_ProjectA* gm = Cast<AGameMode_ProjectA>(GetWorld()->GetAuthGameMode());
	UObject* weapen = NewObject<UObject>(UWeapen);
}

