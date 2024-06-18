// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponEnumType.h"
#include "Weapon.generated.h"

UCLASS()
class HOGWANPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void Tick(float DeltaTime) override;
	void Equip(class UMeshComponent* Mesh, FName SocketName);
protected:
	virtual void BeginPlay() override;

private:
	class UStaticMeshComponent* WeaponMesh;

};
