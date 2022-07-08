// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS_AttributeSet.generated.h"

// Macros to define getters and setters for attributes (AttributeSet.h)
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
  GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECT_A_API UGAS_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
        UGAS_AttributeSet();

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/*Attribute override*/
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    /*
     * Attribute Definitions
     */

     // Health
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
        FGameplayAttributeData Health;
    // Use macros we defined from AttributeSet.h to generate getters and setters
    ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Health);
    UFUNCTION()
        virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

    // Stamina
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
        FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Stamina);
    UFUNCTION()
        virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

    // Attack Power
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mana)
        FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Mana);
    UFUNCTION()
        virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

    /*HealthRegenRate*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_HealthRegenRate)
		FGameplayAttributeData HealthRegenRate;
    ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, HealthRegenRate);
	UFUNCTION()
		virtual void OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate);

	/*StaminaRegenRate*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_StaminaRegenRate)
		FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, StaminaRegenRate);
	UFUNCTION()
		virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate);

	/*ManaRegenRate*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_ManaRegenRate)
		FGameplayAttributeData ManaRegenRate;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, ManaRegenRate);
	UFUNCTION()
		virtual void OnRep_ManaRegenRate(const FGameplayAttributeData& OldManaRegenRate);

	/*MaxHealth*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxHealth);
	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	/*MaxMana*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxMana)
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxMana);
	UFUNCTION()
		virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

	/*MaxStamina*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxStamina);
	UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
};
