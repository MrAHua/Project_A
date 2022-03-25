// Fill out your copyright notice in the Description page of Project Settings.


#include "XTriggerVolume.h"
#include "GameMode_ProjectA.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AXTriggerVolume::AXTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	TriggerZone = CreateDefaultSubobject<UBoxComponent>("BoxComponet");
	TriggerZone->K2_AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AXTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXTriggerVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s entered me"), *(OtherActor->GetName())));

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AGameMode_ProjectA* MyGameMode = Cast<AGameMode_ProjectA>(GameMode);
		MyGameMode->MyStandardDelegate.ExecuteIfBound();
	}
}
void AXTriggerVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s left me"), *(OtherActor -> GetName())));
}