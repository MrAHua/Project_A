// Fill out your copyright notice in the Description page of Project Settings.


#include "Chapter2_CreatingClasses/Potion.h"

// Sets default values
APotion::APotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString APotion::ShowName()
{
	return FString::Printf(TEXT("An instance of UProfile: %s"), *Name);
}

