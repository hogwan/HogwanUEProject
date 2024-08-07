// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Door/Door.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"

ADoor::ADoor()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(Door);

	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(Door);
	
	HunterPos = CreateDefaultSubobject<USceneComponent>(TEXT("HunterPos"));
	HunterPos->SetupAttachment(GetRootComponent());
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOpen && RotTime > 0.f)
	{
		RotTime -= DeltaTime;
		DoorRotate(DeltaTime);
	}

}

void ADoor::Interact()
{
	AActor* ttOwner = GetOwner();
	AHunter* Hunter = Cast<AHunter>(GetOwner());

	if (Hunter && !IsOpen)
	{
		FVector HPos = Hunter->GetActorLocation();
		FVector TargetPos = HunterPos->GetComponentLocation();
		TargetPos.Z = HPos.Z;

		Hunter->SetActorLocation(TargetPos);

		FVector DoorPos = GetActorLocation();
		DoorPos.Z = Hunter->GetActorLocation().Z;

		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(TargetPos, DoorPos);
		Hunter->SetActorRotation(Rot);

		Hunter->PushDoor();
		IsOpen = true;
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADoor::DoorRotate(float _DeltaTime)
{
	DoorRight->AddLocalRotation(FRotator(0.f, RotSpeed * _DeltaTime, 0.f));
	DoorLeft->AddLocalRotation(FRotator(0.f, -RotSpeed * _DeltaTime, 0.f));
}
