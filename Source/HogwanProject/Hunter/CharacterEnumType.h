#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterWeaponState
{
	ECWS_Unoccupied,
	ECWS_OnehandedWeapon,
	ECWS_TwohandedWeapon,
};

UENUM(BlueprintType)
enum class ECharacterGunState
{
	ECGS_Unoccupied,
	ECGS_Equiped,
};

UENUM(BlueprintType)
enum class ECharacterActionState
{
	ECAS_Unoccupied,
	ECAS_Hit,
	ECAS_Attacking,
	ECAS_Dodging,
	ECAS_WeaponSwaping,
};