// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "Warrior.generated.h"

UCLASS()
class PROJECT_A_API AWarrior : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarrior();

	//add abilitysystem
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS_Warrior")
	class UGAS_AbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS_Warrior")
	class UGAS_AttributeSet* Attributes;
	//默认技能
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS_Warrior")
	TArray<TSubclassOf<class UGAS_GameplayAbility>> DefaultAbilities;
	//Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS_Warrior")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS_Warrior")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;
	// Death Animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS_Warrior")
		UAnimMontage* DeathMontage;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual void PossessedBy(AController* NewController) override;
	//初始化属性值
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();
	// Overload to initialize abilities for GAS, and component to store default abilities
	virtual void GiveAbilities();
	//角色是否死亡
	UFUNCTION(BlueprintCallable, Category="GAS_Warrior")
	bool IsDead();
	//角色死亡
	void Die();

	FGameplayTag DeadTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//向前移动
	void MoveForward(float Axis);
	//向右移动
	void MoveRight(float Axis);
	//自拍杆
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;
	//相机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;

	FDelegateHandle HealthChangedDelegateHandle;
	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);

};
