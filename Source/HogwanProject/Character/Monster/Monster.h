// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Monster/BBAICharacter.h"
#include "Interface/HitInterface.h"
#include "Global/BBEnum.h"
#include "Monster.generated.h"

UCLASS()
class HOGWANPROJECT_API AMonster : public ABBAICharacter
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UWidgetComponent* GetLockOnWidget() { return LockOnTargetWidget; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonster MonsterEnum;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* LockOnTargetWidget;

};
