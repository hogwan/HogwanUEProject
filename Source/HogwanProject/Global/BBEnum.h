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

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	EWT_RightHand,
	EWT_LeftHand,
	EWT_TwoHand,
};

UENUM(BlueprintType)
enum class EWeapon : uint8
{
	None,
	EW_LeftFist,
	EW_RightFist,
	EW_SawCleaver,
	EW_SawCleaver_Deformed,
	EW_GreatSword,
	EW_GreatSword_Deformed,
	EW_GreatSword_Sheath,
	EW_Katana,
	EW_Katana_Deformed,
	EW_Katana_Sheath,
	EW_HunterPistol,
};