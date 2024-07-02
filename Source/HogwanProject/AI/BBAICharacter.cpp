// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBAICharacter.h"
#include "AI/BBAIController.h"

void ABBAICharacter::ChangeAnimation(uint8 _Type)
{
	AniValue = _Type;
}

ABBAIController* ABBAICharacter::GetBBAIController()
{
	AController* Con = GetController();

	return Cast<ABBAIController>(GetController());
}

void ABBAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInst = Cast<UBBAIAnimInstance>(GetMesh()->GetAnimInstance());
}
