// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/BBEnum.h"
#include "Weapon.generated.h"

UCLASS()
class HOGWANPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHitType HitType = EHitType::EHT_Light;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
public:	
	virtual void Tick(float DeltaTime) override;
};
