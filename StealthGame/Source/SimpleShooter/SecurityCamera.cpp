// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCamera.h"
#include "PlayerShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CameraAIController.h"

// Sets default values
ASecurityCamera::ASecurityCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CameraGridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera Grid"));
	CameraGridMesh->SetupAttachment(Root);

	CCTVCameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Security Cam"));
	CCTVCameraMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	Controller = Cast<ACameraAIController>(GetController());
}

// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player)
	{
		if (InViewRange() || InSoundRange())
		{
			RotateCameraToPlayer();
		}
		else
		{
			RotateRoutine(DeltaTime);
		}
	}

}

bool ASecurityCamera::InViewRange()
{

	float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	if (Distance <= ViewRange && Controller->LineOfSightTo(Player))
	{
		return true;
	}
	return false;
}

bool ASecurityCamera::InSoundRange()
{

	float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	if (Controller->LineOfSightTo(Player) && Player->CurrentSurfacePhysMaterial)
	{
		switch (Player->CurrentSurfacePhysMaterial->SurfaceType)
		{
			//Wood
		case SurfaceType1:
			if (Distance <= WoodSoundRange)
			{
				return true;
			}
			//Grass
		case SurfaceType2:
			if (Distance <= GrassSoundrange)
			{
				return true;
			}

			//Tile
		case SurfaceType3:
			if (Distance <= TileSoundRange)
			{
				return true;
			}
			//Default
		case SurfaceType_Default:
			break;
		}
	}
	return false;
}

void ASecurityCamera::CheckAlarmCondition()
{
	if (!Player)
	{
		return;
	}
	if (!Player->IsDead() && (InViewRange() || InSoundRange()))
	{
		Alarm();
	}
	IsAlarmTimerSet = false;
}

void ASecurityCamera::Alarm()
{
	OnPlayerDetected.Broadcast(GetActorLocation());
	UGameplayStatics::SpawnSoundAttached(AlarmSound, CCTVCameraMesh);
}

void ASecurityCamera::RotateCameraToPlayer()
{
	FVector ToTarget = Player->GetActorLocation() - GetActorLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw - 100.f, 0.f);
	CCTVCameraMesh->SetWorldRotation(LookAtRotation);
	if (!IsAlarmTimerSet)
	{
		GetWorldTimerManager().SetTimer(AlarmLimitTimerHandle, this, &ASecurityCamera::CheckAlarmCondition, AlarmLimit, false);
		IsAlarmTimerSet = true;
	}
}

void ASecurityCamera::RotateRoutine(float DeltaTime)
{

}