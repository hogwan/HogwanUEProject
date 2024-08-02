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
	Hp = FMath::Clamp(Hp - DamageAmount, 0.f, MaxHp);
	RegainHp = FMath::Clamp(Hp + RegainAmount, Hp, MaxHp);
	RegainTimeRemain = RegainTime;
}

void UAttributeComponent::Heal(float HealAmount)
{
	Hp = FMath::Clamp(Hp + HealAmount, 0.f, MaxHp);
	RegainHp = FMath::Clamp(RegainHp, Hp, MaxHp);
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

}

