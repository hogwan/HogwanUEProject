// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "HUD/HealthBarComponent.h"
#include "ActorComponent/AttributeComponent.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;


	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	Attribute = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(1.f);
	}

}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::GetHit(FVector ImpactPoint)
{
	
}

float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Attribute->ReceiveDamage(Damage);
	HealthBarWidget->SetHealthPercent(Attribute->GetHealthPercent());

	return Damage;
}

