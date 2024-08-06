// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/Monster/Monster.h"
#include "Interface/HitInterface.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Box"));
	SetRootComponent(Sphere);

	Flying = CreateDefaultSubobject<UNiagaraComponent>("Flying");
	Flying->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnCollisionBeginOverlap);
}

void ABullet::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IHitInterface* Hit = Cast<IHitInterface>(OtherActor);
	if (Hit)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor);
		if (Character)
		{
			UGameplayStatics::ApplyDamage(Character, Damage, GetOwner()->GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
		}

		if (HitEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				HitEffect,
				GetActorLocation()
			);
		}

		Hit->GetHit(GetActorLocation(),this, EHitType::EHT_Bullet);
		Destroy();
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;
	if (LifeTime < 0.f)
	{
		Destroy();
	}

	AddActorWorldOffset(GetActorForwardVector() * Speed * DeltaTime);
}

