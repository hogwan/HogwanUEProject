#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterWeaponState : uint8
{
	ECWS_Unoccupied,
	ECWS_OnehandedWeapon,
	ECWS_TwohandedWeapon,
};

UENUM(BlueprintType)
enum class ECharacterGunState : uint8
{
	ECGS_Unoccupied,
	ECGS_Equiped,
};

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	ECAS_Unoccupied,
	ECAS_Hit,
	ECAS_Attacking,
	ECAS_Dodging,
	ECAS_WeaponSwaping,
	ECAS_TakeDown,
	ECAS_Deform,
	ECAS_Throw,
	ECAS_Drink,
	ECAS_PushDoor,
	ECAS_TurnOn,
	ECAS_Sit,
	ECAS_Death,
	ECAS_Kick,
};