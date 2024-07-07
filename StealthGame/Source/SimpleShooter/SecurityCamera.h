// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SecurityCamera.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDetectedSignature, FVector, CameraLoc);


UCLASS()
class SIMPLESHOOTER_API ASecurityCamera : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	ASecurityCamera();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDetectedSignature OnPlayerDetected;

private:

	bool InViewRange();
	bool InSoundRange();
	void CheckAlarmCondition();
	void Alarm();
	void RotateCameraToPlayer();
	void RotateRoutine(float DeltaTime);

	FTimerHandle AlarmLimitTimerHandle;
	float CurrentRotation = 0.f;
	bool IsAlarmTimerSet = false;
	class APlayerShooterCharacter* Player;
	class ACameraAIController* Controller;


	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CameraGridMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CCTVCameraMesh;

	UPROPERTY(EditAnywhere)
	USoundBase* AlarmSound;

	UPROPERTY(EditAnywhere, Category = "ViewRange")
	float ViewRange = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Alarms")
	float AlarmLimit = 3.f;

	UPROPERTY(EditAnywhere, Category = "Sound Range")
	float GrassSoundrange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Sound Range")
	float TileSoundRange = 500.f;

	UPROPERTY(EditAnywhere, Category = "Sound Range")
	float WoodSoundRange = 2500.f;

};
