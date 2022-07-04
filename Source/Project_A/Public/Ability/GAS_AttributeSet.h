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

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
        FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, AttackPower);

    UFUNCTION()
        virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);

    /*Talent skill points*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FGameplayAttributeData SkillPoint;
};
