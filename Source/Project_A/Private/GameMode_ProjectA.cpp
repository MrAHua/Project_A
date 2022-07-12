// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_ProjectA.h"
#include "Engine/World.h"
#include "Chapter6_InputandCollision/Warrior.h"
#include "Hala.h"
#include "GameStateBase_ProjectA.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AGameMode_ProjectA::AGameMode_ProjectA()
{
	DefaultPawnClass = AHala::StaticClass();
	GameStateClass = AGameStateBase_ProjectA::StaticClass();

	RespawnDelay = 5.0f;
	if (!HeroClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find HeroClass. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	}
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

void AGameMode_ProjectA::CharacterDieAndRespawn(AController* Controller)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorClass, Controller->GetPawn()->GetActorTransform(), SpawnParameters);
	Controller->UnPossess();
	Controller->Possess(SpectatorPawn);

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate;

	RespawnDelegate = FTimerDelegate::CreateUObject(this, &AGameMode_ProjectA::CharacterRespawn, Controller);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);
}

void AGameMode_ProjectA::CharacterRespawn(AController* Controller)
{
	if (Controller->IsPlayerController())
	{
		// Respawn player hero
		AActor* PlayerStart = FindPlayerStart(Controller);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AWarrior* Hero = GetWorld()->SpawnActor<AWarrior>(HeroClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParameters);
		APawn* OldSpectatorPawn = Controller->GetPawn();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("find cameras in scene>>"));
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Hero);
	}
	else
	{
		// Respawn AI hero
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AWarrior* Hero = GetWorld()->SpawnActor<AWarrior>(HeroClass, EnemySpawnPoint->GetActorTransform(), SpawnParameters);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Hero);
	}
}

void AGameMode_ProjectA::initGameState() {
	AGameMode_ProjectA* gm = Cast<AGameMode_ProjectA>(GetWorld()->GetAuthGameMode());
	UObject* weapen = NewObject<UObject>(UWeapen);
}

void AGameMode_ProjectA::BeginPlay()
{
	Super::BeginPlay();

	// Get the enemy hero spawn point
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor->GetName() == FString("EnemyHeroSpawn"))
		{
			EnemySpawnPoint = Actor;
			break;
		}
	}

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

