// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/FogDoor.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"

// Sets default values
AFogDoor::AFogDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	SetRootComponent(BoxCol);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(GetRootComponent());

}

void AFogDoor::BeginPlay()
{
	Super::BeginPlay();

	FogOff();
	
}

void AFogDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFogDoor::FogOn()
{
	BoxCol->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Effect->SetVisibility(true);
}

void AFogDoor::FogOff()
{
	BoxCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Effect->SetVisibility(false);
}

