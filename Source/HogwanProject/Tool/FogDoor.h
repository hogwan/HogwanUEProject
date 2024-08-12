// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogDoor.generated.h"

UCLASS()
class HOGWANPROJECT_API AFogDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFogDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* Effect;

	void FogOn();
	void FogOff();

};
