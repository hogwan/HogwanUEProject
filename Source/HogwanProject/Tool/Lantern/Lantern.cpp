// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Lantern/Lantern.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Hunter/BBPlayerController.h"
#include "NiagaraComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/KismetMathLibrary.h"

ALantern::ALantern()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	TurnOnEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TurnOnEffect"));
	TurnOnEffect->SetupAttachment(GetRootComponent());
	TurnOnEffect->SetVisibility(false);
}

void ALantern::BeginPlay()
{
	Super::BeginPlay();
}

void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALantern::Interact()
{
	Super::Interact();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	AHunter* Hunter = Cast<AHunter>(GetOwner());

	FVector LanternPos = GetActorLocation();
	LanternPos.Z = 0.f;

	FVector HunterPos = Hunter->GetActorLocation();
	HunterPos.Z = 0.f;

	FRotator HunterRot = UKismetMathLibrary::FindLookAtRotation(HunterPos, LanternPos);
	FVector LanternToHunterVec = HunterPos - LanternPos;
	LanternToHunterVec.Normalize();

	Hunter->SetActorRotation(HunterRot);
	Hunter->SetActorLocation(GetActorLocation() + LanternToHunterVec * InteractDistance);
	

	if (!IsOn)
	{
		Hunter->TurnOnLantern();
	}
	else
	{
		Hunter->SitDown();
	}
}

void ALantern::TurnOn()
{
	IsOn = true;
	TurnOnEffect->SetVisibility(true);
}
