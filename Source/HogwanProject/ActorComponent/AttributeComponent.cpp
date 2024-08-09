// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

float UAttributeComponent::GetHealthPercent()
{
	if (MaxHp == 0.f) return 1.f;

	return Hp / MaxHp;
}

float UAttributeComponent::GetHunterMaxHealthPercent()
{
	return MaxHp / Limited;
}

float UAttributeComponent::GetHunterHealthPercent()
{
	return Hp / Limited;
}

float UAttributeComponent::GetHunterRegainHealthPercent()
{
	return RegainHp / Limited;
}

float UAttributeComponent::GetHunterMaxStaminaPercent()
{
	return MaxStamina / Limited;
}

float UAttributeComponent::GetHunterStaminaPercent()
{
	return Stamina/ Limited;
}

void UAttributeComponent::ReceiveDamage(float DamageAmount)
{
	RegainTimeRemain = RegainTime;

	Hp = FMath::Clamp(Hp - DamageAmount, 0.f, MaxHp);
	RegainHp = FMath::Clamp(Hp + RegainAmount, Hp, MaxHp);
}

void UAttributeComponent::ConsumeStamina(float ConsumeAmount)
{
	Stamina = FMath::Clamp(Stamina - ConsumeAmount, 0, MaxStamina);
}

void UAttributeComponent::Heal(float HealAmount)
{
	Hp = FMath::Clamp(Hp + HealAmount, 0.f, MaxHp);
	RegainHp = FMath::Clamp(RegainHp, Hp, MaxHp);
}

void UAttributeComponent::Regain()
{
	float Gap = RegainHp - Hp;
	
	if (FMath::IsNearlyZero(Gap)) return;

	Hp = FMath::Clamp(Hp + MaxHp / 10.f, 0.f, RegainHp);
}

bool UAttributeComponent::GetIsDeath()
{
	return FMath::IsNearlyZero(Hp);
}


void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	RegainTimeRemain -= DeltaTime;

	if (RegainTimeRemain < 0.f)
	{
		RegainHp = Hp;
	}

}

