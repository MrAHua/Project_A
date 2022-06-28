// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_ProjectA.h"
#include "Hala.h"
#include "GameStateBase_ProjectA.h"
#include "..\Public\GameMode_ProjectA.h"

AGameMode_ProjectA::AGameMode_ProjectA()
{
	DefaultPawnClass = AHala::StaticClass();
	GameStateClass = AGameStateBase_ProjectA::StaticClass();
}
void AGameMode_ProjectA::DestroyActorFunction()
{
	if (HealthPotion != nullptr) {
		HealthPotion->Destroy();
	}
}

void AGameMode_ProjectA::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AGameMode_ProjectA::initGameState() {
	AGameMode_ProjectA* gm = Cast<AGameMode_ProjectA>(GetWorld()->GetAuthGameMode());
	UObject* weapen = NewObject<UObject>(UWeapen);
}

void AGameMode_ProjectA::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Actor Spawning"));

	FTransform SpawnLocation;
	GetWorld()->SpawnActor<APotion>(APotion::StaticClass(), SpawnLocation);

	HealthPotion = GetWorld()->SpawnActor<APotion>(APotion::StaticClass(), SpawnLocation);
	if (HealthPotion != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("HealthPotion Spawned"));
		//设置定时器执行传入的函数
		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, this, &AGameMode_ProjectA::DestroyActorFunction, 10);
	}
}

