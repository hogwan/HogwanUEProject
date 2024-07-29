// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SerpmareSpitProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Projectile/SerpmareSwamp.h"

ASerpmareSpitProjectile::ASerpmareSpitProjectile()
{
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(Sphere);
    ProjectileMovementComponent->InitialSpeed = 3000.0f;
    ProjectileMovementComponent->MaxSpeed = 3000.0f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void ASerpmareSpitProjectile::ProjectileExplosion()
{
	if (HitEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			HitEffect,
			GetActorLocation()
		);
	}

	if (Swamp)
	{
		ASerpmareSwamp* SpawnSwamp = GetWorld()->SpawnActor<ASerpmareSwamp>(Swamp, GetActorTransform());
		SpawnSwamp->SetActorRotation(FRotator::ZeroRotator);
	}


	Destroy();
}
