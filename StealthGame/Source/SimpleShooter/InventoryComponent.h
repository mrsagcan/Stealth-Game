// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void DecreaseRifleAmmoAmount(int Amount);
	void DecreaseLauncherAmmoAmount(int Amount);
	void ReduceHealthPacks();

	UFUNCTION(BlueprintCallable)
	int GetRifleAmmoAmount();

	UFUNCTION(BlueprintCallable)
	int GetLauncherAmmoAmount();

	UFUNCTION(BlueprintCallable)
	int GetHealthPacksAmount();

private:

	UPROPERTY(EditDefaultsOnly)
	int RifleAmmoAmount = 120;

	UPROPERTY(EditDefaultsOnly)
	int LauncherAmmoAmount = 60;

	UPROPERTY(EditDefaultsOnly)
	int HealthPacksAmount = 5;
};
