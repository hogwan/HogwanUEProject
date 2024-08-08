// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/BBGameInstance.h"
#include "Character/Monster/BBAICharacter.h"

void UBBGameInstance::ResetAllMonster()
{
	for (ABBAICharacter* Monster : AllMonsters)
	{
		if (Monster != nullptr)
		{
			Monster->Destroy();
		}
	}

	AllMonsters.Empty();

	for (const FSpawnInfo& SpawnInfo : AllSpawnInfo)
	{
		FTransform SpawnTrans;
		SpawnTrans.SetLocation(SpawnInfo.SpawnPos);

		ABBAICharacter* Monster = GetWorld()->SpawnActor<ABBAICharacter>(SpawnInfo.SpawnClass, SpawnTrans);
		Monster->SetActorRotation(SpawnInfo.SpawnRot);

		for (const FVector& PatrolPoint : SpawnInfo.PatrolPoints)
		{
			Monster->PatrolPoints.Add(PatrolPoint);
		}

		Monster->EditMode = false;

		AllMonsters.Add(Monster);
	}
}
