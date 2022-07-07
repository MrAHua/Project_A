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

void APlayerState_ProjectA::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &APlayerState_ProjectA::MaxHealthChanged);
	}
	AWarrior* Warrior = Cast<AWarrior>(GetPawn());
	MaxHealth = Warrior->Attributes->GetMaxHealth();
}


void APlayerState_ProjectA::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	MaxHealth = Data.NewValue;

}
