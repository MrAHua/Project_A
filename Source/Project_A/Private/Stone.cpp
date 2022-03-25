// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone.h"

// Sets default values
AStone::AStone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StoneLifeTime = 10;
	IsDead = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	//auto from c++11,instead of code :ConstrctorHelpers::FObjectFinder<UStaticMesh>
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshAsset.Object != nullptr) {
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AStone::BeginPlay()
{
	Super::BeginPlay();
	//设置Actor的生命周期
	if (IsDead)
	{
		SetLifeSpan(StoneLifeTime);

	}
}

// Called every frame
void AStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

