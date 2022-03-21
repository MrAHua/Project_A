// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_ProjectA.h"
#include "..\Public\GameMode_ProjectA.h"

void AGameMode_ProjectA::DestroyActorFunction()
{
	if (HealthPotion != nullptr) {
		HealthPotion->Destroy();
	}
}

void AGameMode_ProjectA::initGameState() {
	AGameMode_ProjectA* gm = Cast<AGameMode_ProjectA>(GetWorld()->GetAuthGameMode());
	UObject* weapen = NewObject<UObject>(UWeapen);
}

void AGameMode_ProjectA::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Actor Spawning"));

	FTransform SpawnLocation;
	GetWorld()->SpawnActor<APotion>(APotion::StaticClass(), SpawnLocation);

	HealthPotion = GetWorld()->SpawnActor<APotion>(APotion::StaticClass(), SpawnLocation);
	if (HealthPotion != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("HealthPotion Spawned"));
		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, this, &AGameMode_ProjectA::DestroyActorFunction, 10);
	}
}

