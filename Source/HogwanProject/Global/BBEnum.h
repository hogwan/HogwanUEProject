#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	EMS_Unable,
	EMS_Idle,
	EMS_Patrol,
	EMS_Turn,
	EMS_Rotate,
	EMS_Perceive,
	EMS_Run,
	EMS_Attack,
	EMS_DashAttack,
	EMS_Dead,
	EMS_BackStep,
	EMS_Lull,
	EMS_Shoot,
	EMS_BackWalk,
	EMS_PatternTerm,
	EMS_Wait,
	EMS_Dodge,
};

UENUM(BlueprintType)
enum class EHitType : uint8
{
	None,
	EHT_Light=2,
	EHT_Bullet=3,
	EHT_Heavy=4,
	EHT_Charge=5,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	EWT_MeleeWeapon,
	EWT_RangedWeapon,
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

UENUM(BlueprintType)
enum class EMonster : uint8
{
	None,
	EM_Zombie,
	EM_Parasite,
	EM_Wolf,
	EM_InfectedSolider,
	EM_Priest,
	EM_Mutant,
};

UENUM(BlueprintType)
enum class EToughness : uint8
{
	None,
	ET_Low = 2,
	ET_Medium = 4,
	ET_High = 7
};

UENUM(BlueprintType)
enum class EDir : uint8
{
	None,
	Left,
	Right,
	Back,
	Forward,
};

UENUM(BlueprintType)
enum class EItem : uint8
{
	None,
	Potion,
	Bullet,
	FireBottle,
	Stone,
	SawCleaver,
	GreatSword,
	Katana,
	HunterPistol,
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	UseItem,
	Weapon,
};