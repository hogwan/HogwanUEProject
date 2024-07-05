#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	EMS_Unable,
	EMS_Idle,
	EMS_Patrol,
	EMS_Turn,
	EMS_Perceive,
	EMS_Run,
	EMS_Attack, 
	EMS_Dead,
};

UENUM(BlueprintType)
enum class EHitType : uint8
{
	EHT_Light,
	EHT_Heavy,
	EHT_Charge,
	EHT_Bullet,
};