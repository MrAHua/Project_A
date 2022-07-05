// Fill out your copyright notice in the Description page of Project Settings.


#include "Chapter6_InputandCollision/Warrior.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
//GAS
#include "Ability/GAS_AbilitySystemComponent.h"
#include "Ability/GAS_AttributeSet.h"
#include "Ability/GAS_GameplayAbility.h"

#include "GameFramework/SpringArmComponent.h"

// Sets default values
AWarrior::AWarrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//添加技能系统
	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent ->SetIsReplicated(true);
	AbilitySystemComponent ->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	Attributes = CreateDefaultSubobject<UGAS_AttributeSet>(TEXT("AttributeSet"));

	//自拍杆
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	//视角相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom);
	//设置角色自身旋转跟随移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	//控制器是否直接控制角色旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	//控制器是否直接控制自拍杆旋转
	CameraBoom->bUsePawnControlRotation = true;
	//控制器是否直接控制相机旋转
	FollowCamera->bUsePawnControlRotation = false;
	
}

UAbilitySystemComponent* AWarrior::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;;
}

void AWarrior::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

    // Owner and Avatar are bother this character
    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    InitializeAttributes();
	AddStartupEffects();
    GiveAbilities();
}

void AWarrior::InitializeAttributes()
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

void AWarrior::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || AbilitySystemComponent == nullptr || AbilitySystemComponent->StartupEffectsApplied)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("apply start effects."));
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
}

void AWarrior::GiveAbilities()
{
	 // If the server has the authority to grant abilities and there is a valid ASC
    if (HasAuthority() && AbilitySystemComponent)
    {
        // Foreach ability in DefaultAbilities, grant the ability
        for (TSubclassOf<UGAS_GameplayAbility>& StartupAbility : DefaultAbilities)
        {
            // `1` below is the level of the ability, which could later be used to allow abilities to scale with player level
            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
        }
    }
}

// Called when the game starts or when spawned
void AWarrior::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定轴映射
	PlayerInputComponent->BindAxis("MoveForward", this, &AWarrior::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWarrior::MoveRight);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,&AWarrior::Jump);

	  // Make sure GAS is valid along with player input component
	if (AbilitySystemComponent && InputComponent)
	{
		 // Where the 3rd parameter is a string equal to enum typename defined in unrealgame5.h
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGASAbilityInputID", static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}


void AWarrior::MoveForward(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Axis);
}

void AWarrior::MoveRight(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, Axis);
}
