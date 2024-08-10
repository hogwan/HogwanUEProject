// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Serpmare.h"
#include "HUD/HealthBarComponent.h"
#include "ActorComponent/AttributeComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/GameplayStatics.h"

ASerpmare::ASerpmare()
{
	PrimaryActorTick.bCanEverTick = true;

	LockOnTargetWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnTarget"));
	LockOnTargetWidget->SetupAttachment(GetRootComponent());
	
	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	BoxCol->SetupAttachment(GetMesh(), FName(TEXT("HitBoxSocket")));
}

void ASerpmare::BeginPlay()
{
	Super::BeginPlay();

	if (LockOnTargetWidget)
	{
		LockOnTargetWidget->SetVisibility(false);
	}	

	BoxCol->OnComponentBeginOverlap.AddDynamic(this, &ASerpmare::HitBoxBeginOverlap);
}

void ASerpmare::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		UGameplayStatics::ApplyDamage(
			Hunter,
			Damage,
			GetOwner()->GetInstigatorController(),
			this,
			UDamageType::StaticClass());

		IHitInterface* Hit = Cast<IHitInterface>(Hunter);
		if (Hit)
		{
			Hit->GetHit(Hunter->GetActorLocation(), GetOwner(), HitType);
		}
	}
}


void ASerpmare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASerpmare::Reset()
{
	Super::Reset();

}
void ASerpmare::GetHit(const FVector& _ImpactPoint, AActor* _Hitter, EHitType _HitType)
{
	Super::GetHit(_ImpactPoint, _Hitter, _HitType);
}

void ASerpmare::DisableHitBox()
{
	BoxCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASerpmare::EnableHitBox()
{
	BoxCol->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

