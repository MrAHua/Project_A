// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
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
	//默认属性
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS_Warrior")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual void PossessedBy(AController* NewController) override;
	//初始化属性值
	virtual void InitializeAttributes();
	// Overload to initialize abilities for GAS, and component to store default abilities
	virtual void GiveAbilities();

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

};
