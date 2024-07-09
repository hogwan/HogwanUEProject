// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RangedWeapon.h"
#include "Weapon/Bullet.h"
#include "Character/Hunter/Hunter.h"
#include "Global/BBGameInstance.h"

ARangedWeapon::ARangedWeapon()
{
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnPoint->SetupAttachment(GetRootComponent());
}

void ARangedWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARangedWeapon::SpawnBullet()
{
	FTransform SpawnTrans = BulletSpawnPoint->GetComponentTransform();

	UWorld* World = GetWorld();

	ABullet* NewBullet = World->SpawnActor<ABullet>(BP_Bullet, SpawnTrans);

	if (nullptr == NewBullet) return;

	UBBGameInstance* GameInstance = Cast<UBBGameInstance>(GetGameInstance());
	
	if (GameInstance && GameInstance->LockOnTarget)
	{
		FVector Dir = GameInstance->LockOnTarget->GetActorLocation() - SpawnTrans.GetLocation();

		Dir.Normalize();

		NewBullet->SetDir(Dir);
	}
	else
	{
		if (GetOwner())
		{
			NewBullet->SetDir(GetOwner()->GetActorForwardVector());
		}
	}

}

void ARangedWeapon::BeginPlay()
{
	//블루프린트의 비긴플레이가 먼저 실행되서 위로 올림
	WeaponType = EWeaponType::EWT_LeftHand;
	
	Super::BeginPlay();
}
