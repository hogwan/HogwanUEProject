// Fill out your copyright notice in the Description page of Project Settings.


#include "BBAnimInstance.h"
#include "Hunter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBBAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Hunter = Cast<AHunter>(TryGetPawnOwner());
	if (Hunter)
	{
		HunterMovement = Hunter->GetCharacterMovement();
	}
}

void UBBAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (HunterMovement)
	{
		MoveVector = HunterMovement->Velocity;
		GroundSpeed = UKismetMathLibrary::VSizeXY(MoveVector);
	}
}
