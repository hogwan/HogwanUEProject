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

void UAttributeComponent::ReceiveDamage(float DamageAmount)
{
	Hp = FMath::Clamp(Hp - DamageAmount, 0.f, MaxHp);
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

