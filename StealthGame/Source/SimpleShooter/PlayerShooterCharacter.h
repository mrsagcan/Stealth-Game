// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "PlayerShooterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API APlayerShooterCharacter : public AShooterCharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	APlayerShooterCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintPure)
	AGun* GetEquippedWeapon() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentSurface(UPhysicalMaterial* PhysMat);


	UPROPERTY()
	UPhysicalMaterial* CurrentSurfacePhysMaterial;


private:

	float InitialMaxWalkSpeed = 0;
	float InitialFOV = 0;
	class UCameraComponent* Camera;
	class UInventoryComponent* Inventory;
	class UCharacterMovementComponent* CharacterMovement;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	virtual void Reload() override;
	void NextWeapon();
	void PreviousWeapon();
	void HandleCrouch();
	void Run();
	void TurnBackToWalking();
	void Aim();
	void AimBack();
	void UseHealthPack();
	void SpawnHealthPacks();

	UPROPERTY(EditDefaultsOnly, Category = "Walk Speed")
	float MaxRunningSpeed = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Walk Speed")
	float MaxWalkSpeedWhenAiming = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float AimedFOV = 35.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHealthPack> HealthPackClass;

	UPROPERTY()
	TArray<AHealthPack*> HealthPacks;


};
