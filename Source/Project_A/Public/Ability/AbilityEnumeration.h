// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EGASAbilityInputID:uint8
{
	// 0 None
	None = 0 UMETA(DisplayName = "None"),
	Confirm,
	Cancel,
	Attack
};