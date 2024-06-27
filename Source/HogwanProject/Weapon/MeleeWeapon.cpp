// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "Interface/HitInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

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
}

void AMeleeWeapon::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult HitResult;

	IgnoreArray.AddUnique(this);

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		BoxTraceStart->GetComponentLocation(),
		BoxTraceEnd->GetComponentLocation(),
		FVector(3.f, 3.f, 3.f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		IgnoreArray,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);

	if (HitResult.GetActor())
	{
		UGameplayStatics::ApplyDamage(
			HitResult.GetActor(),
			20.f,
			GetOwner()->GetInstigatorController(),
			this,
			UDamageType::StaticClass());

		IgnoreArray.AddUnique(HitResult.GetActor());
		IHitInterface* Hit = Cast<IHitInterface>(HitResult.GetActor());
		if (Hit)
		{
			Hit->GetHit(HitResult.ImpactPoint);
		}
	}

}
