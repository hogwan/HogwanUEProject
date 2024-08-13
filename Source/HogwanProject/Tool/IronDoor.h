// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IronDoor.generated.h"

UCLASS()
class HOGWANPROJECT_API AIronDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AIronDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCol;

	UPROPERTY(EditAnywhere)
	float UpDistance = 500.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 500.f;

	UPROPERTY(EditAnywhere)
	bool IsOpen = false;

	void Open();
};
