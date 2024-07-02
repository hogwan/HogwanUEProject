// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BBAIController.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ABBAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABBAIController();

	UFUNCTION(BlueprintCallable)
	void ChangeAIState(uint8 _StateType);

};
