// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/HitInterface.h"

AMeleeWeapon::AMeleeWeapon()
{
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(Mesh);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceStart"));
	BoxTraceStart->SetupAttachment(Mesh);

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceEnd"));
	BoxTraceEnd->SetupAttachment(Mesh);
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnBoxBeginOverlap);
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EquipHand = EEquipHand::EEH_RightHand;
}

void AMeleeWeapon::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult HitResult;

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		BoxTraceStart->GetComponentLocation(),
		BoxTraceEnd->GetComponentLocation(),
		FVector(5.f, 5.f, 5.f),
		Mesh->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		IgnoreArray,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);

	if (HitResult.GetActor())
	{
		IgnoreArray.AddUnique(HitResult.GetActor());
	}

	IHitInterface* Hit = Cast<IHitInterface>(HitResult.GetActor());

	if (Hit)
	{
		Hit->GetHit();
	}

}

void AMeleeWeapon::HitBoxOn()
{
	IgnoreArray.AddUnique(this);
	IgnoreArray.AddUnique(Owner);
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::HitBoxOff()
{
	IgnoreArray.Empty();
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
