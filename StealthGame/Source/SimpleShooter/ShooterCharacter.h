// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class AHealthPack;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnWeapons();
	void ActivateWeapon(int32 Index);
	virtual void Reload();


	int32 AmmoToLoad = 0;
	int32 ActiveIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float Health = 10.f;

	UPROPERTY()
	TArray<AGun*> Guns;


public:	

	// Sets default values for this character's properties
	AShooterCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;


	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;


private:

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGun>> GunClasses;

};
