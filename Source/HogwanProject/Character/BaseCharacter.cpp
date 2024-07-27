// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "ActorComponent/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"
#include "MotionWarpingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Attribute = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
	
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));


}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(1.f);
	}
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType)
{
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			ImpactPoint
		);
	}

	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			ImpactPoint
		);
	}

	if (NiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			NiagaraSystem,
			ImpactPoint
		);
	}

	if (BloodSmoke)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			BloodSmoke,
			ImpactPoint
		);
	}
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Attribute->ReceiveDamage(Damage);
	HealthBarWidget->SetHealthPercent(Attribute->GetHealthPercent());

	return Damage;
}

bool ABaseCharacter::BackHit(AActor* Hitter)
{
	FVector Forward = GetActorForwardVector();
	Forward.Z = 0.f;

	FVector Target = Hitter->GetActorLocation() - GetActorLocation();
	Target.Z = 0.f;

	Forward.Normalize();
	Target.Normalize();

	float DotScala = UKismetMathLibrary::Dot_VectorVector(Forward, Target);

	float RadianAngle = UKismetMathLibrary::Acos(DotScala);

	float DegreeAngle = FMath::RadiansToDegrees(RadianAngle);

	if (DegreeAngle > 120.f)
	{
		return true;
	}

	return false;
}

void ABaseCharacter::ResetState()
{
}

