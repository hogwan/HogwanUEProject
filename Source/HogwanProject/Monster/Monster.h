// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "Monster.generated.h"

UCLASS()
class HOGWANPROJECT_API AMonster : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void GetHit() override;

protected:
	virtual void BeginPlay() override;

};
