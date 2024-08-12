// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SerpmareSwamp.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/GameplayStatics.h"

ASerpmareSwamp::ASerpmareSwamp()
{
	PrimaryActorTick.bCanEverTick = true;
	
	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	SetRootComponent(HitBox);

	SwampEffect = CreateDefaultSubobject<UNiagaraComponent>("Effect");
	SwampEffect->SetupAttachment(GetRootComponent());
}

void ASerpmareSwamp::BeginPlay()
{
	Super::BeginPlay();
	
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASerpmareSwamp::SwampCollide);

}

void ASerpmareSwamp::HitBoxOn()
{
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASerpmareSwamp::HitBoxOff()
{
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASerpmareSwamp::SwampCollide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		Hunter->GetHit(Hunter->GetActorLocation(), this, EHitType::EHT_Light);
		UGameplayStatics::ApplyDamage(Hunter,Damage,nullptr, this, UDamageType::StaticClass());
	}
}


void ASerpmareSwamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	LifeTime -= DeltaTime;
	DamageTickTimeAcc -= DeltaTime;

	if (LifeTime < 0.f)
	{
		Destroy();
	}

	
	if (IsHitBoxOn)
	{
		HitBoxOff();
		IsHitBoxOn = false;
	}

	if (DamageTickTimeAcc < 0.f)
	{
		DamageTickTimeAcc = DamageTickTime;
		IsHitBoxOn = true;
		HitBoxOn();
	}
}

