#pragma once
#include "ColoredTexture.generated.h"

USTRUCT( BlueprintType )
struct FColoredTexture
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UTexture* Texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		FLinearColor Color;
};
