// Fill out your copyright notice in the Description page of Project Settings.


#include "Chapter2_CreatingClasses/Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	ChildSceneComponent = CreateDefaultSubobject<USceneComponent>("ChildSceneComponet");
	BoxOne = CreateDefaultSubobject<UStaticMeshComponent>("BoxOne");
	BoxTwo = CreateDefaultSubobject<UStaticMeshComponent>("BoxTwo");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	auto MeshAssetSphere = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshAsset.Object != nullptr) {
		BoxOne->SetStaticMesh(MeshAsset.Object);
		BoxOne->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}
	if (MeshAssetSphere.Object != nullptr) {
		BoxTwo->SetStaticMesh(MeshAssetSphere.Object);
		BoxTwo->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}
	RootComponent = Root;
	BoxOne->K2_AttachTo(Root);
	BoxTwo->K2_AttachTo(ChildSceneComponent);
	ChildSceneComponent->K2_AttachTo(Root);
	/*BoxOne->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	BoxTwo->AttachToComponent(ChildSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ChildSceneComponent->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);*/
	ChildSceneComponent->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(250, 0, 0), FVector(0.5f)));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

