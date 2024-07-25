// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Monster.h"
#include "HUD/HealthBarComponent.h"
#include "ActorComponent/AttributeComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/GameplayStatics.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	LockOnTargetWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnTarget"));
	LockOnTargetWidget->SetupAttachment(GetRootComponent());

	MonsterHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	MonsterHitBox->SetupAttachment(GetRootComponent());

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	BoxTraceStart->SetupAttachment(MonsterHitBox);

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	BoxTraceEnd->SetupAttachment(MonsterHitBox);

}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	if (LockOnTargetWidget)
	{
		LockOnTargetWidget->SetVisibility(false);
	}

	MonsterHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMonster::HitBoxBeginOverlap);
	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMonster::DisableHitBox()
{
	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IgnoreArray.Empty();
}

void AMonster::EnableHitBox()
{
	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMonster::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AMonster::Reset()
{
	Super::Reset();

	MonsterHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IgnoreArray.Empty();
}

void AMonster::GetHit(const FVector& _ImpactPoint, AActor* _Hitter, EHitType _HitType)
{
	Super::GetHit(_ImpactPoint, _Hitter, _HitType);
}

