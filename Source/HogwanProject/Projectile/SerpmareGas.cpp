// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SerpmareGas.h"
#include "Components/SphereComponent.h"

void ASerpmareGas::BeginPlay()
{
	Super::BeginPlay();
}
void ASerpmareGas::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorWorldOffset(GetActorForwardVector() * Speed * _DeltaTime);

	//Sphere->SetSphereRadius()
}
