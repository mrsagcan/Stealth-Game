// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InventoryComponent.h"
#include "HealthPack.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"

APlayerShooterCharacter::APlayerShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovement = GetCharacterMovement();
	InitialMaxWalkSpeed = CharacterMovement->MaxWalkSpeed;

	Inventory = GetComponentByClass<UInventoryComponent>();
	if (Inventory)
	{
		SpawnHealthPacks();
	}

	Camera = GetComponentByClass<UCameraComponent>();
	if (Camera)
	{
		InitialFOV = Camera->FieldOfView;
	}
}

void APlayerShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("NextWeapon"), EInputEvent::IE_Pressed, this, &APlayerShooterCharacter::NextWeapon);
	PlayerInputComponent->BindAction(TEXT("PreviousWeapon"), EInputEvent::IE_Pressed, this, &APlayerShooterCharacter::PreviousWeapon);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &APlayerShooterCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &APlayerShooterCharacter::HandleCrouch);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &APlayerShooterCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &APlayerShooterCharacter::TurnBackToWalking);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &APlayerShooterCharacter::Aim);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &APlayerShooterCharacter::AimBack);
	PlayerInputComponent->BindAction(TEXT("UseMedkit"), EInputEvent::IE_Released, this, &APlayerShooterCharacter::UseHealthPack);
}

AGun* APlayerShooterCharacter::GetEquippedWeapon() const
{
	return Guns[ActiveIndex];
}

void APlayerShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerShooterCharacter::Reload()
{
	Super::Reload();
	if (AmmoToLoad == 0)
	{
		return;
	}
	auto CurrentGun = Guns[ActiveIndex];
	if (CurrentGun->Name == "Rifle")
	{
		if (Inventory->GetRifleAmmoAmount() == 0)
		{
			return;
		}
		Inventory->DecreaseRifleAmmoAmount(AmmoToLoad);
	}
	else if (CurrentGun->Name == "Launcher")
	{
		if (Inventory->GetLauncherAmmoAmount() == 0)
		{
			return;
		}
		Inventory->DecreaseLauncherAmmoAmount(AmmoToLoad);
	}
}

void APlayerShooterCharacter::NextWeapon()
{
	Super::ActivateWeapon(ActiveIndex + 1);
}

void APlayerShooterCharacter::PreviousWeapon()
{
	Super::ActivateWeapon(ActiveIndex - 1);
}

void APlayerShooterCharacter::HandleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void APlayerShooterCharacter::Run()
{
	CharacterMovement->MaxWalkSpeed = MaxRunningSpeed;
}

void APlayerShooterCharacter::TurnBackToWalking()
{
	CharacterMovement->MaxWalkSpeed = InitialMaxWalkSpeed;
}

void APlayerShooterCharacter::Aim()
{
	Camera->FieldOfView = AimedFOV;
	CharacterMovement->MaxWalkSpeed = MaxWalkSpeedWhenAiming;
}

void APlayerShooterCharacter::AimBack()
{
	Camera->FieldOfView = InitialFOV;
	CharacterMovement->MaxWalkSpeed = InitialMaxWalkSpeed;
}

void APlayerShooterCharacter::UseHealthPack()
{
	if (HealthPacks.Num() == 0)
	{
		return;
	}
	if (Health == MaxHealth)
	{
		return;
	}
	auto HealthPackToUse = HealthPacks[0];
	if (Health + HealthPackToUse->GetHeal() > MaxHealth)
	{
		Health = MaxHealth;
	}
	else
	{
		Health += HealthPackToUse->GetHeal();
	}
	Inventory->ReduceHealthPacks();
	HealthPacks.Remove(HealthPackToUse);
	HealthPackToUse->Destroy();
}

void APlayerShooterCharacter::SpawnHealthPacks()
{
	for (int i = 0; i < Inventory->GetHealthPacksAmount(); i++)
	{
		AHealthPack* HealthPack = GetWorld()->SpawnActor<AHealthPack>(HealthPackClass);
		HealthPack->SetOwner(this);
		HealthPacks.Add(HealthPack);
	}
}


void APlayerShooterCharacter::SetCurrentSurface(UPhysicalMaterial* PhysMat)
{
	CurrentSurfacePhysMaterial = PhysMat;
}
