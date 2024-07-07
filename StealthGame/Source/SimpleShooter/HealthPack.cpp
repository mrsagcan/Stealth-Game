// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
}

float AHealthPack::GetHeal()
{
	return HealAmount;
}

