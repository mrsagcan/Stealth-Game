// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIShooterCharacter.h"



void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		auto AIPawn = Cast<AAIShooterCharacter>(GetPawn());

		if (AIPawn)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("FirstPatrolLocation"), AIPawn->FirstPatrolLocation + AIPawn->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastPatrolLocation"), AIPawn->LastPatrolLocation + AIPawn->GetActorLocation());
		}
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


bool AShooterAIController::IsDead() const
{
	auto ControlledCharacter = Cast<AAIShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}

void AShooterAIController::AlarmAI()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	IsAlarmed = true;
	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
}
