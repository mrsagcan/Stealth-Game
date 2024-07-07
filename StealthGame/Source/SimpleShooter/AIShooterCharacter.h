// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "AIShooterCharacter.generated.h"

class ASecurityCamera;

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AAIShooterCharacter : public AShooterCharacter
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	AAIShooterCharacter();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AlarmTheEnemyActor(FVector CameraLoc);

	
	UPROPERTY(EditAnywhere, Category = "Patrolling", Meta = (MakeEditWidget = "true"))
	FVector FirstPatrolLocation;

	UPROPERTY(EditAnywhere, Category = "Patrolling", Meta = (MakeEditWidget = "true"))
	FVector LastPatrolLocation;

	UPROPERTY(EditAnywhere, Category = "Alarm State")
	float AlarmRange = 1000.f;

};
