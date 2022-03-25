// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrack.h"
#include "BarracksUnit.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABarrack::ABarrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	SpawnPoint = CreateDefaultSubobject<UParticleSystemComponent>("SpawnPoint");
	SpawnInterval = 10;
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		BuildingMesh->SetStaticMesh(MeshAsset.Object);
		BuildingMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}
	auto ParticleSystem = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Engine/Tutorial/SubEditors/TutorialAssets/TutorialParticleSystem.TutorialParticleSystem'"));
	if (ParticleSystem.Object != nullptr)
	{
		SpawnPoint->SetTemplate(ParticleSystem.Object);
	}
	SpawnPoint->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	UnitToSpawn = ABarracksUnit::StaticClass();
}

// Called when the game starts or when spawned
void ABarrack::BeginPlay()
{
	Super::BeginPlay();
	RootComponent = BuildingMesh;
	SpawnPoint->K2_AttachTo(RootComponent);
	SpawnPoint->SetRelativeLocation(FVector(150, 0, 0));
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this, &ABarrack::SpawnUnit, SpawnInterval, true);
}

// Called every frame
void ABarrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrack::SpawnUnit()
{
	FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	GetWorld()->SpawnActor(UnitToSpawn, &SpawnLocation);
}

void ABarrack::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}
