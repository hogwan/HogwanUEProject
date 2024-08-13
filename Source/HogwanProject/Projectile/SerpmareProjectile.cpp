// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SerpmareProjectile.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/GameplayStatics.h"
#include "Global/BBGameInstance.h"
#include "Sound/SoundAttenuation.h"


ASerpmareProjectile::ASerpmareProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);

	Flying = CreateDefaultSubobject<UNiagaraComponent>("Flying");
	Flying->SetupAttachment(GetRootComponent());
}

void ASerpmareProjectile::BeginPlay()
{
	Super::BeginPlay();


	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASerpmareProjectile::ProjectileCollide);
}

void ASerpmareProjectile::ProjectileExplosion()
{
	if (HitEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			HitEffect,
			GetActorLocation()
		);
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());

	if (GameIns->SoundMap[TEXT("Explosion")])
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			GameIns->SoundMap[TEXT("Explosion")],
			GetActorLocation(),
			1.f,
			1.f,
			0.f,
			GameIns->BBAttenuation
		);
	}

	Destroy();
}

void ASerpmareProjectile::ProjectileCollide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);
	
	if (OtherActor == this) return;

	if (Hunter)
	{
		Hunter->GetHit(GetActorLocation(), GetOwner(), EHitType::EHT_Light);
		UGameplayStatics::ApplyDamage(Hunter, Damage, nullptr, this, UDamageType::StaticClass());
	}

	ProjectileExplosion();
}

void ASerpmareProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;

	if (LifeTime < 0.f)
	{
		ProjectileExplosion();
	}

}

