
\Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/Elevator.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SpotLight.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	ElevatorMesh->SetupAttachment(SceneComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ElevatorAsset(TEXT("StaticMesh'/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh'"));
	if (ElevatorAsset.Succeeded())
	{
		ElevatorMesh->SetStaticMesh(ElevatorAsset.Object);
		ElevatorMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		ElevatorMesh->SetWorldScale3D(FVector(0.5f));;
	}
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(SceneComponent);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnOverlapBegin); 
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnOverlapEnd); 
	ElevatorSpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("ElevatorSpotLight"));
	ElevatorSpotLight->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AElevator::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		ElevatorSpotLight->Intensity = 50000.0f;
		ElevatorSpotLight->SetLightColor(FLinearColor(255.0f,0.0f,0.0f,0.0f));
	}

	widgetBlackLinesInstance = CreateWidget<UUserWidget>(GetWorld(), widgetBlackLines);
	widgetBlackLinesInstance->AddToViewport();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->bShowMouseCursor = true;
}

void AElevator::OnOverlapEnd(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
		ElevatorSpotLight->Intensity = 50000.0f;
		ElevatorSpotLight->SetLightColor(FLinearColor(0.0f, 0.0f, 255.0f, 0.0f));
		if (widgetBlackLinesInstance != nullptr)
		{
			widgetBlackLinesInstance->RemoveFromViewport();
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
		}
		
	}
}

void AElevator::MoveToTargetFloor(const FVector& TargetFloorLocation)
{
	
}

