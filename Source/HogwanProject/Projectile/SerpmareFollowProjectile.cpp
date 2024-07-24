// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SerpmareFollowProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/Hunter.h"


void ASerpmareFollowProjectile::BeginPlay()
{
	Super::BeginPlay();

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	Target = GameIns->Hunter;
}

void ASerpmareFollowProjectile::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	IdleAcc -= _DeltaTime;

	if (IdleAcc < 0.f && Target && !FollowTarget)
	{
		FollowTarget = true;
		
		FVector TargetPos = Target->GetActorLocation();
		FVector ProjectilePos = GetActorLocation();

		FRotator FindRot = UKismetMathLibrary::FindLookAtRotation(ProjectilePos, TargetPos);

		SetActorRotation(FindRot);

	}

	if (FollowTarget)
	{
		AddActorWorldOffset(GetActorForwardVector() * Speed * _DeltaTime);

		FVector TargetPos = Target->GetActorLocation();
		FVector ProjectilePos = GetActorLocation();

		FRotator FindRot = UKismetMathLibrary::FindLookAtRotation(ProjectilePos, TargetPos);
		FRotator StartRot = GetActorRotation();
		FRotator Result = UKismetMathLibrary::RInterpTo(StartRot, FindRot, _DeltaTime, 3.f);

		SetActorRotation(Result);
	}
}
