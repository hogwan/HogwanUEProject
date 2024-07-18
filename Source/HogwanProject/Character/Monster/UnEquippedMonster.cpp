// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/UnEquippedMonster.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Hunter/Hunter.h"

AUnEquippedMonster::AUnEquippedMonster()
{
	MonsterHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	MonsterHitBox->SetupAttachment(GetRootComponent());

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	BoxTraceStart->SetupAttachment(MonsterHitBox);

	BoxTraceEnd= CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	BoxTraceEnd->SetupAttachment(MonsterHitBox);
}

void AUnEquippedMonster::BeginPlay()
{
	Super::BeginPlay();

	MonsterHitBox->OnComponentBeginOverlap.AddDynamic(this, &AUnEquippedMonster::HitBoxBeginOverlap);
	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AUnEquippedMonster::DisableHitBox()
{
	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IgnoreArray.Empty();
}

void AUnEquippedMonster::EnableHitBox()
{
	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AUnEquippedMonster::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult HitResult;

	IgnoreArray.AddUnique(this);
	IgnoreArray.AddUnique(GetOwner());

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		BoxTraceStart->GetComponentLocation(),
		BoxTraceEnd->GetComponentLocation(),
		FVector(10.f, 10.f, 10.f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		IgnoreArray,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);

	AHunter* Hunter = Cast<AHunter>(HitResult.GetActor());

	if (Hunter)
	{
		UGameplayStatics::ApplyDamage(
			HitResult.GetActor(),
			Damage,
			GetOwner()->GetInstigatorController(),
			this,
			UDamageType::StaticClass());

		IgnoreArray.AddUnique(Hunter);
		IHitInterface* Hit = Cast<IHitInterface>(HitResult.GetActor());
		if (Hit)
		{
			Hit->GetHit(HitResult.ImpactPoint, GetOwner(), HitType);
		}
	}

}

void AUnEquippedMonster::Reset()
{
	Super::Reset();

	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IgnoreArray.Empty();
}

void AUnEquippedMonster::GetHit(const FVector& _ImpactPoint, AActor* _Hitter, EHitType _HitType)
{
	Super::GetHit(_ImpactPoint, _Hitter, _HitType);

}

