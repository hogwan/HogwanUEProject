// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SerpmareProjectile.h"
#include "Components/SphereComponent.h"

ASerpmareProjectile::ASerpmareProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());
}

void ASerpmareProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void ASerpmareProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;

	if (LifeTime < 0.f)
	{
		Destroy();
	}

}

