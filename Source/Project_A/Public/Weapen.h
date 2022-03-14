// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ColoredTexture.h"
#include "EnumName.h"
#include "Weapen.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class PROJECT_A_API UWeapen : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats )
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats )
		float Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		FString Name;
	//Use USTRUCT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		FColoredTexture Color;
	//Use UENUM
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		TEnumAsByte<Status> status;
	//œ‚«∂±¶ Ø
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		TSubclassOf<AActor> GemStone;
	UPROPERTY(EditAnywhere, meta = (MetaClass = "GameMode"), Category = Unit ) 
		FSoftClassPath UClassGameMode;//ue5 now called, ue4 call FStringClassReference
};
