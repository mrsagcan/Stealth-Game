// Fill out your copyright notice in the Description page of Project Settings.


//TODO: Add Main Menu
	//Play button.
	//Settings button.
		//Sound setting
		//Graphics quality setting
		//Brightness setting
	//Quit button.

#include "ShooterCharacter.h"
#include "Gun.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
	Health = MaxHealth;
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

void AShooterCharacter::Shoot()
{
	Guns[ActiveIndex]->PullTrigger();
}

void AShooterCharacter::Reload()
{
	auto CurrentGun = Guns[ActiveIndex];
	AmmoToLoad = CurrentGun->MaxAmmo - CurrentGun->Ammo;
	if (AmmoToLoad == 0)
	{
		return;
	}
	CurrentGun->Reload(AmmoToLoad);
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

void AShooterCharacter::SpawnWeapons()
{
	for (auto GunClass : GunClasses)
	{
		AGun* Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->SetOwner(this);
		Guns.Add(Gun);
	}
	ActivateWeapon(0);
}

void AShooterCharacter::ActivateWeapon(int32 Index)
{
	for (auto Weapon : Guns)
	{
		Weapon->SetActorHiddenInGame(true);
	}
	ActiveIndex = Index < 0 ? Index + Guns.Num() : Index % Guns.Num();
	Guns[ActiveIndex]->SetActorHiddenInGame(false);
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}


