// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ThrowObject.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AThrowObject::AThrowObject()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void AThrowObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThrowObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

