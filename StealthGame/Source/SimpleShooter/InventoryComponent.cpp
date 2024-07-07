// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "HealthPack.h"
#include "Gun.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::DecreaseRifleAmmoAmount(int Amount)
{
	RifleAmmoAmount -= Amount;
}

void UInventoryComponent::DecreaseLauncherAmmoAmount(int Amount)
{
	LauncherAmmoAmount -= Amount;
}

void UInventoryComponent::ReduceHealthPacks()
{
	HealthPacksAmount--;
}

int UInventoryComponent::GetRifleAmmoAmount()
{
	return RifleAmmoAmount;
}

int UInventoryComponent::GetLauncherAmmoAmount()
{
	return LauncherAmmoAmount;
}

int UInventoryComponent::GetHealthPacksAmount()
{
	return HealthPacksAmount;
}

