// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SerpmareProjectile.generated.h"

UCLASS()
class HOGWANPROJECT_API ASerpmareProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASerpmareProjectile();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float LifeTime = 6.f;
protected:
	virtual void BeginPlay() override;


};
