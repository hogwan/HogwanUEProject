// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowObject.generated.h"

UCLASS()
class HOGWANPROJECT_API AThrowObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowObject();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

};
