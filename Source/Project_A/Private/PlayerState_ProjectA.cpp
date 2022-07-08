// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState_ProjectA.h"
#include "Ability/GAS_AbilitySystemComponent.h"
#include "Chapter6_InputandCollision/Warrior.h"
#include "Ability/GAS_AttributeSet.h"

APlayerState_ProjectA::APlayerState_ProjectA()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSetBase = CreateDefaultSubobject<UGAS_AttributeSet>(TEXT("AttributeSetBase"));
}

class UAbilitySystemComponent* APlayerState_ProjectA::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

class UGAS_AttributeSet* APlayerState_ProjectA::GetAttributeSet() const
{
	return AttributeSetBase;
}

float APlayerState_ProjectA::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float APlayerState_ProjectA::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float APlayerState_ProjectA::GetMana() const
{
	return AttributeSetBase->GetMana();
}

float APlayerState_ProjectA::GetMaxMana() const
{
	return AttributeSetBase->GetMaxMana();
}

float APlayerState_ProjectA::GetStamina() const
{
	return AttributeSetBase->GetStamina();
}

float APlayerState_ProjectA::GetMaxStamina() const
{
	return AttributeSetBase->GetMaxStamina();
}

float APlayerState_ProjectA::GetHealthRegenRate() const
{
	return AttributeSetBase->GetHealthRegenRate();
}

float APlayerState_ProjectA::GetManaRegenRate() const
{
	return AttributeSetBase->GetManaRegenRate();
}

float APlayerState_ProjectA::GetStaminaRegenRate() const
{
	return AttributeSetBase->GetStaminaRegenRate();
}

void APlayerState_ProjectA::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &APlayerState_ProjectA::MaxHealthChanged);
	}
	AWarrior* Warrior = Cast<AWarrior>(GetPawn());
	MaxHealth = GetMaxHealth();
		//Warrior->Attributes->GetMaxHealth();
}


void APlayerState_ProjectA::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	MaxHealth = Data.NewValue;

}
