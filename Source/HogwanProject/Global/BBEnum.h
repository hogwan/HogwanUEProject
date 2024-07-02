#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	EMS_Idle,
	EMS_Patrol,
	EMS_Turn,
	EMS_Perceive,
	EMS_Run,
	EMS_Attack, 
};

UENUM(BlueprintType)
enum class EMonsterAnimation : uint8
{
	EMA_Idle,
	EMA_Walk,
	EMA_Turn_Right,
	EMA_Turn_Left,
	EMA_Perceive,
	EMA_Run,
	EMA_Attack0,
	EMA_Attack1,
	EMA_Attack2,
};