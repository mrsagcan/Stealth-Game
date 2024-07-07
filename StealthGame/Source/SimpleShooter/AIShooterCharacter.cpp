// Fill out your copyright notice in the Description page of Project Settings.

#include "AIShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SecurityCamera.h"
#include "ShooterAIController.h"

AAIShooterCharacter::AAIShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASecurityCamera::StaticClass(), Cameras);
	for (auto Actor : Cameras)
	{
		ASecurityCamera* SecurityCam = Cast<ASecurityCamera>(Actor);
		if (SecurityCam)
		{
			SecurityCam->OnPlayerDetected.AddUniqueDynamic(this, &AAIShooterCharacter::AlarmTheEnemyActor);
		}
	}
}

void AAIShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAIShooterCharacter::AlarmTheEnemyActor(FVector CameraLoc)
{
	float Distance = FVector::Dist(GetActorLocation(), CameraLoc);
	if (Distance <= AlarmRange)
	{
		Cast<AShooterAIController>(GetController())->AlarmAI();
	}
}