// Fill out your copyright notice in the Description page of Project Settings.


#include "Chapter6_InputandCollision/Warrior.h"

// Sets default values
AWarrior::AWarrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWarrior::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Controller)
	{
		float len = lastInput.Size();
		if (len > 1.f)
			lastInput /= len;
		AddMovementInput(GetActorForwardVector(), lastInput.Y);
		AddMovementInput(GetActorRightVector(), lastInput.X);
		// Zero off last input values
		lastInput =FVector(0,0,0);
	}
}

// Called to bind functionality to input
void AWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AWarrior::Forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWarrior::Right);
	PlayerInputComponent->BindAxis("Right", this, &AWarrior::Right);
	PlayerInputComponent->BindAxis("Left", this, &AWarrior::Left);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,&AWarrior::Jump);
}

void AWarrior::Forward(float amount)
{
	if (Controller && amount)
	{
		lastInput.Y += amount;
	}
}

void AWarrior::Back(float amount)
{
	if (Controller && amount)
	{
		lastInput.Y += -amount;
	}
}

void AWarrior::Right(float amount)
{
	if (Controller && amount)
	{
		lastInput.X += amount;
	}
}

void AWarrior::Left(float amount)
{
	if (Controller && amount)
	{
		lastInput.X += -amount;
	}
}
