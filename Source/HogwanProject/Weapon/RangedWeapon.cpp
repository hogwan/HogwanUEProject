// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RangedWeapon.h"
#include "Weapon/Bullet.h"
#include "Character/Hunter/Hunter.h"
#include "Global/BBGameInstance.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActorComponent/InventoryComponent.h"

ARangedWeapon::ARangedWeapon()
{
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnPoint->SetupAttachment(GetRootComponent());
}

void ARangedWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARangedWeapon::SpawnBullet(AActor* Target)
{
	FTransform SpawnTrans = BulletSpawnPoint->GetComponentTransform();

	UWorld* World = GetWorld();

	ABullet* NewBullet = World->SpawnActor<ABullet>(BP_Bullet, SpawnTrans);

	if (nullptr == NewBullet) return;
	NewBullet->SetOwner(this);
	NewBullet->Damage = WeaponBaseDamage;

	if (LaunchEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			LaunchEffect,
			SpawnTrans.GetLocation()
		);
	}

	if (Target)
	{
		FRotator FindRot = UKismetMathLibrary::FindLookAtRotation(SpawnTrans.GetLocation(), Target->GetActorLocation());
		NewBullet->SetActorRotation(FindRot);

	}
	else
	{
		if (GetOwner())
		{
			NewBullet->SetActorRotation(GetOwner()->GetActorRotation());
		}
	}

	if (AHunter* Hunter = Cast<AHunter>(GetOwner()))
	{
		for (FInvenSlotData& Data : Hunter->GetInventory()->Inventory)
		{
			if (Data.Item == EItem::Bullet)
			{
				Data.Number--;
			}
		}
		Hunter->PotionBulletUpdate();
	}
}

void ARangedWeapon::BeginPlay()
{
	//블루프린트의 비긴플레이가 먼저 실행되서 위로 올림
	WeaponType = EWeaponType::EWT_RangedWeapon;
	
	Super::BeginPlay();
}
