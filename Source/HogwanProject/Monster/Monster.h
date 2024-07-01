// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "Interface/HitInterface.h"
#include "Monster.generated.h"

UCLASS()
class HOGWANPROJECT_API AMonster : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void Tick(float DeltaTime) override;


	FORCEINLINE class UWidgetComponent* GetLockOnWidget() { return LockOnTargetWidget; }
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* LockOnTargetWidget;

};
