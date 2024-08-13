// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/DoorSwitch.h"
#include "Tool/IronDoor.h"
#include "Components/SphereComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/KismetMathLibrary.h"

ADoorSwitch::ADoorSwitch()
{
	HunterPos = CreateDefaultSubobject<USceneComponent>(TEXT("HunterPos"));
	HunterPos->SetupAttachment(GetRootComponent());
}

void ADoorSwitch::Interact()
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

		Hunter->Kick();
	}
	
}

void ADoorSwitch::OpenDoor()
{
	if (ConnectedDoor)
	{
		ConnectedDoor->Open();
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
