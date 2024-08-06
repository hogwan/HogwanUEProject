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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType = EWeaponType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeapon Weapon = EWeapon::None;

	UFUNCTION(BlueprintCallable)
	void SetActive(bool Check);

	UFUNCTION(BlueprintCallable)
	FString GetName()
	{
		return WeaponName + "_";
	}

	UPROPERTY(EditAnywhere)
	float WeaponBaseDamage = 1.f;

	UPROPERTY(EditAnywhere)
	float DamageScale = 5.f;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
public:	
	virtual void Tick(float DeltaTime) override;
};
