// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBAICharacter.h"

void ABBAICharacter::ChangeAnimation(uint8 _Type)
{
	AniValue = _Type;
}

void ABBAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInst = Cast<UBBAIAnimInstance>(GetMesh()->GetAnimInstance());
}
