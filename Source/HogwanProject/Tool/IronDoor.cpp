// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/IronDoor.h"
#include "Components/BoxComponent.h"

AIronDoor::AIronDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	SetRootComponent(BoxCol);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

}

void AIronDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIronDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOpen)
	{
		if (UpDistance < 0.f) return;

		UpDistance -= OpenSpeed * DeltaTime;
		AddActorWorldOffset(FVector::UpVector * OpenSpeed * DeltaTime);
	}

}

void AIronDoor::Open()
{
	IsOpen = true;
}

