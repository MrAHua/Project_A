// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(Blueprintable)
class PROJECT_A_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	/*如果没有添加VisibleAnywhere修饰，会造成在Editor细节面板无法显示附加到Root的层级关系*/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* ChildSceneComponent;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BoxOne;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BoxTwo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
