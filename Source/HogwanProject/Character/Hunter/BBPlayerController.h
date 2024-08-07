// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Global/BBEnum.h"
#include "BBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ABBPlayerController : public APlayerController
{
	GENERATED_BODY()

	void BeginPlay() override;
	

public:
	UPROPERTY(EditAnywhere)
	TMap<EInputMode, class UInputWidget*> AllInputTypeUI;

	UPROPERTY(EditAnywhere, Category = Input)
	TMap<EInputMode,class UInputMappingContext*> InputMappingContextArrays;

	UFUNCTION(BlueprintCallable)
	void SetInputMode(EInputMode _InputMode);

	UFUNCTION(BlueprintCallable)
	void OpenWidget(EInputMode _InputMode);

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

	UPROPERTY(VisibleAnywhere)
	EInputMode CurInputMode = EInputMode::Play;

};
