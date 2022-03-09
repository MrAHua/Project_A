// Fill out your copyright notice in the Description page of Project Settings.


#include "Hala.h"

// Sets default values
AHala::AHala()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHala::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHala::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHala::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

