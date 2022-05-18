// Fill out your copyright notice in the Description page of Project Settings.


#include "Hala.h"

// Sets default values
AHala::AHala()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");
	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->bUsePawnControlRotation = 0;
}

// Called when the game starts or when spawned
void AHala::BeginPlay()
{
	Super::BeginPlay();
	MainCamera->SetupAttachment(RootComponent);
}

// Called every frame
void AHala::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!MovementInput.IsZero())
	{
		MovementInput *= 100;
		FVector InputVector = FVector(0, 0, 0);
		InputVector += GetActorForwardVector() * MovementInput.X * DeltaTime;
		InputVector += GetActorRightVector() * MovementInput.Y * DeltaTime;
		GetCharacterMovement()->AddInputVector(InputVector);
		//GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, FString::Printf(TEXT("x- %f, y - %f, z - % f"),InputVector.X, InputVector.Y, InputVector.Z));
	}
	if (!CameraInput.IsNearlyZero())
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Pitch += CameraInput.Y;
		NewRotation.Yaw += CameraInput.X;
		APlayerController* MyPlayerController = Cast<APlayerController>(GetController());
		if (MyPlayerController != nullptr)
		{
			MyPlayerController->AddYawInput(CameraInput.X);
			MyPlayerController->AddPitchInput(CameraInput.Y);
		}
		SetActorRotation(NewRotation);
	}
}

// Called to bind functionality to input
void AHala::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("DropItem", EInputEvent::IE_Pressed, this, &AHala::DropItem);
	InputComponent->BindAxis("MoveForward", this, &AHala::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHala::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &AHala::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &AHala::YawCamera);
}

void AHala::DropItem()
{
	if (MyInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	AInventoryActor* Item = MyInventory -> CurrentInventory.Last();
	MyInventory->RemoveFromInventory(Item);
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);
}

void AHala::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	MyInventory->AddToInventory(InventoryItem);
}

void AHala::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, 
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);
	}
}

void AHala::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}
void AHala::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}
void AHala::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}
void AHala::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}
