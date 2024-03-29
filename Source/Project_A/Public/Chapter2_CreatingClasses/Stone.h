// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stone.generated.h"

UCLASS()
class PROJECT_A_API AStone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStone();
	//添加静态网格体组件
	UPROPERTY()
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		float StoneLifeTime;
	UPROPERTY(EditAnywhere)
		bool IsDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
