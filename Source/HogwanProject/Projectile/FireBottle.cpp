// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FireBottle.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Monster/Monster.h"
#include "Projectile/Explosion.h"

void AFireBottle::ColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ColBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	GetWorld()->SpawnActor<AExplosion>(Explosion,GetActorTransform());

	Destroy();
}
