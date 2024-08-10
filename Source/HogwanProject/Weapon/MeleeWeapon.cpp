// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "Interface/HitInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Monster/Monster.h"
#include "Character/Hunter/Hunter.h"
#include "ActorComponent/AttributeComponent.h"
#include "Global/BBGameInstance.h"
#include "Particles/ParticleSystemComponent.h"

AMeleeWeapon::AMeleeWeapon()
{
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(GetRootComponent());

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceStart"));
	BoxTraceStart->SetupAttachment(HitBox);

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceEnd"));
	BoxTraceEnd->SetupAttachment(HitBox);

}

void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeleeWeapon::HitBoxOn()
{
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::HitBoxOff()
{
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IgnoreArray.Empty();
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::HitBoxBeginOverlap);
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponType = EWeaponType::EWT_MeleeWeapon;
}

void AMeleeWeapon::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult HitResult;

	IgnoreArray.AddUnique(this);
	IgnoreArray.AddUnique(GetOwner());

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		BoxTraceStart->GetComponentLocation(),
		BoxTraceEnd->GetComponentLocation(),
		BoxTraceSize,
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		IgnoreArray,
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	ABaseCharacter* Character = Cast<ABaseCharacter>(HitResult.GetActor());

	if (Character)
	{
		IHitInterface* Hit = Cast<IHitInterface>(HitResult.GetActor());
		if (Hit)
		{
			Hit->GetHit(HitResult.ImpactPoint, GetOwner(), HitType);
		}

		IgnoreArray.AddUnique(Character);

		AHunter* Hunter = Cast<AHunter>(GetOwner());

		if (Hunter)
		{
			Hunter->GetAttribute()->Regain();

			Hunter->StatusUpdate();

			UGameplayStatics::ApplyDamage(
				HitResult.GetActor(),
				Hunter->GetCurDamage(Hunter->CurStatus.Strength),
				GetOwner()->GetInstigatorController(),
				this,
				UDamageType::StaticClass());
		}

		ABBAICharacter* Monster = Cast<ABBAICharacter>(GetOwner());
		if (Monster)
		{
			UGameplayStatics::ApplyDamage(
				HitResult.GetActor(),
				Monster->Damage,
				GetOwner()->GetInstigatorController(),
				this,
				UDamageType::StaticClass());
		}

	}

}
