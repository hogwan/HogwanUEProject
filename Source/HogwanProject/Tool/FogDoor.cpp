// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/FogDoor.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFogDoor::AFogDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	SetRootComponent(BoxCol);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(GetRootComponent());

	Sphere->SetupAttachment(GetRootComponent());

	HunterPos = CreateDefaultSubobject<USceneComponent>(TEXT("HunterPos"));
	HunterPos->SetupAttachment(GetRootComponent());


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

void AFogDoor::Interact()
{
	Super::Interact();

	AHunter* Hunter = Cast<AHunter>(GetOwner());

	if (Hunter)
	{
		FVector HPos = Hunter->GetActorLocation();
		FVector TargetPos = HunterPos->GetComponentLocation();
		TargetPos.Z = HPos.Z;

		Hunter->SetActorLocation(TargetPos);

		FVector DoorPos = GetActorLocation();
		DoorPos.Z = Hunter->GetActorLocation().Z;

		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(TargetPos, DoorPos);
		Hunter->SetActorRotation(Rot);

		Hunter->PassFog();
	}

}

void AFogDoor::FogOn()
{
	BoxCol->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Effect->SetVisibility(true);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFogDoor::FogOff()
{
	BoxCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Effect->SetVisibility(false);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

