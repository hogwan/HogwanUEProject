// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Stone.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Monster/Monster.h"

void AStone::ColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ColBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AMonster* Monster = Cast<AMonster>(OtherActor);

	if (Monster)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, nullptr, nullptr);
		Monster->GetHit(GetActorLocation(), this, EHitType::EHT_Light);
	}

	Destroy();
}
