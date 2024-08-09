// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Global/BBEnum.h"
#include "BBGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector SpawnPos;

	UPROPERTY(EditAnywhere)
	FRotator SpawnRot;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABBAICharacter> SpawnClass;

	UPROPERTY(EditAnywhere)
	TArray<FVector> PatrolPoints;
};

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* LockOnTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHunter* Hunter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABBHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABBPlayerController* BBPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UTexture2D*> TextureMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItem, UTexture2D*> EnumTextureMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, TSubclassOf<AActor>> ThrowObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItem, FString> ItemExplain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, class USoundBase*> SoundMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpawnInfo> AllSpawnInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ABBAICharacter*> AllMonsters;

	UFUNCTION(BlueprintCallable)
	void ResetAllMonster();

};
