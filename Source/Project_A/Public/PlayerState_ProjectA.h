// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "PlayerState_ProjectA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API APlayerState_ProjectA : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APlayerState_ProjectA();

	// Implement IAbilitySystemInterface
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAttribute")
		class UGAS_AttributeSet* AttributeSetBase;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerAttribute")
	float MaxHealth;
	UPROPERTY()
	class UGAS_AbilitySystemComponent* AbilitySystemComponent;


	FDelegateHandle MaxHealthChangedDelegateHandle;

	virtual void BeginPlay() override;

	// Attribute changed callbacks
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
};
