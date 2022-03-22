// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateBase_ProjectA.h"

AGameStateBase_ProjectA::AGameStateBase_ProjectA()
{
	CurrentScore = 0;
}

void AGameStateBase_ProjectA::SetScore(int32 NewScore)
{
	CurrentScore = NewScore;
}

int32 AGameStateBase_ProjectA::GetScore()
{
	return CurrentScore;
}
