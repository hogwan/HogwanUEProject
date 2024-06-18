#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	EWT_RightHand,
	EWT_LeftHand,
};

UENUM(BlueprintType)
enum class ERightHandWeapon : uint8
{
	None,
	ERHW_SawCleaver,
	ERHW_LudwigSword,
};

UENUM(BlueprintType)
enum class ELeftHandWeapon : uint8
{
	None,
	ELHW_Pistol,
};