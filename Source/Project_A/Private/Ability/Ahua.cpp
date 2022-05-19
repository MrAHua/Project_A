// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Ahua.h"

// Sets default values
AAhua::AAhua()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	Attributes = CreateDefaultSubobject<UGAS_AttributeSet>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void AAhua::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAhua::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAhua::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Make sure GAS is valid along with player input component
  if (AbilitySystemComponent && InputComponent)
  {
    // Where the 3rd parameter is a string equal to enum typename defined in unrealgame5.h
    const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGASAbilityInputID", static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
    AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
  }
}

UAbilitySystemComponent* AAhua::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAhua::InitializeAttributes()
{
    // If the ASC and DefaultAttributeEffect objects are valid
    if (AbilitySystemComponent && DefaultAttributeEffect)
    {
        // Create context object for this gameplay effecct
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);

        // Create an outgoing effect spec using the effect to apply and the context
        FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

        if (SpecHandle.IsValid())
        {
            // Apply the effect using the derived spec
            // + Could be ApplyGameplayEffectToTarget() instead if we were shooting a target
            FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
        }
    }
}

void AAhua::GiveAbilities()
{
    // If the server has the authority to grant abilities and there is a valid ASC
    if (HasAuthority() && AbilitySystemComponent)
    {
        // Foreach ability in DefaultAbilities, grant the ability
        for (TSubclassOf<UGAS_GameplayAbility>& StartupAbility : DefaultAbilities)
        {
            // `1` below is the level of the ability, which could later be used to allow abilities to scale with player level
            //AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
        }
    }
}

void AAhua::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // Owner and Avatar are bother this character
    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    InitializeAttributes();
    GiveAbilities();
}

void AAhua::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    InitializeAttributes();

    if (AbilitySystemComponent && InputComponent)
    {
        // Where the 3rd parameter is a string equal to enum typename defined in unrealgame5.h
        const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGASAbilityInputID", static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
        AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
    }
}

