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
	
	class UGAS_AttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetMana() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetMaxMana() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetStamina() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetHealthRegenRate() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetManaRegenRate() const;
	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
		float GetStaminaRegenRate() const;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerAttribute")
	float MaxHealth;
	UPROPERTY()
	class UGAS_AbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAttribute")
	class UGAS_AttributeSet* AttributeSetBase;


	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle HealthChagedDelegateHandle;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	// Attribute changed callbacks
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
};
