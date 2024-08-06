// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Explosion.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Character/Monster/Monster.h"
#include "Kismet/GameplayStatics.h"

AExplosion::AExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(GetRootComponent());
}

void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AExplosion::ColBeginOverlap);
}

void AExplosion::ColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMonster* Monster = Cast<AMonster>(OtherActor);

	if (Monster)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, nullptr, nullptr);
		Monster->GetHit(GetActorLocation(), this, EHitType::EHT_Heavy);
	}
}

void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;
	if (LifeTime < 0.f)
	{
		Destroy();
	}
}

