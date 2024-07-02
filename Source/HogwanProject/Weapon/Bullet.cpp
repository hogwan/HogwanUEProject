// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/Monster/Monster.h"
#include "Interface/HitInterface.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Box"));
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnCollisionBeginOverlap);
}

void ABullet::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMonster* Monster = Cast<AMonster>(OtherActor);
	if (Monster)
	{
		//만약 몬스터의 상태가 공격중이라면 스턴 , ApplyDamage
	}

	IHitInterface* Hit = Cast<IHitInterface>(OtherActor);
	if (Hit)
	{
		Hit->GetHit(GetActorLocation());
	}

	//Destroy();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;
	if (LifeTime < 0.f)
	{
		Destroy();
	}

	AddActorWorldOffset(Dir * Speed * DeltaTime);
}

