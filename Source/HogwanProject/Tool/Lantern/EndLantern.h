// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool/InteractObject.h"
#include "EndLantern.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API AEndLantern : public AInteractObject
{
	GENERATED_BODY()
	
public:
	void Interact() override;
};
