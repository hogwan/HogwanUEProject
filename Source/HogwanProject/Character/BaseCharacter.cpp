// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "ActorComponent/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"
#include "MotionWarpingComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Attribute = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
	
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(1.f);
	}
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType)
{

}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Attribute->ReceiveDamage(Damage);
	HealthBarWidget->SetHealthPercent(Attribute->GetHealthPercent());

	return Damage;
}

