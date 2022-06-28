// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Chapter2_CreatingClasses/Item.h"
#include "Chapter2_CreatingClasses/Potion.h"
#include "Blueprint/UserWidget.h"
#include "GameMode_ProjectA.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FStandardDelegateSignature)
DECLARE_DELEGATE_OneParam(FParamDelegateSignature, FLinearColor)
UCLASS()
class PROJECT_A_API AGameMode_ProjectA : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameMode_ProjectA();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UClassNames)
		TSubclassOf<UItem> UWeapen;
	UPROPERTY()
		APotion* HealthPotion;

	/* When Game start, this is the used widget*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	/* Instance to be Menu*/
	UUserWidget* CurrentWidget;


public:
	void initGameState();
	virtual void BeginPlay() override;

	UFUNCTION()
	void DestroyActorFunction();
	/* Removed current menu widget and specify a new widget */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	FStandardDelegateSignature MyStandardDelegate;
	FStandardDelegateSignature PointLightOutDelegate;
	FParamDelegateSignature MyParameterDelegate;
};
