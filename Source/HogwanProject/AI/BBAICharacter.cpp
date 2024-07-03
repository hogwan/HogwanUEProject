// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBAICharacter.h"
#include "AI/BBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/BBEnum.h"
#include "AI/BBAIAnimInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"
#include "Kismet/KismetMathLibrary.h"


ABBAIController* ABBAICharacter::GetBBAIController()
{
	AController* Con = GetController();

	return Cast<ABBAIController>(GetController());
}

void ABBAICharacter::GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType)
{
	Super::GetHit(ImpactPoint, Hitter, HitType);

	ABBAIController* Con = Cast<ABBAIController>(GetController());
	
	if (Con && AnimInst)
	{
		UBlackboardComponent* BlackBoard = Con->GetBlackboardComponent();
		if (BlackBoard)
		{
			BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Unable));
		}

		if (HitType == EHitType::EHT_Light)
		{
			AnimInst->Montage_Play(AnimInst->HitMontage);
			AnimInst->Montage_JumpToSection(TEXT("Hit1"));
		}
		else if (HitType == EHitType::EHT_Heavy)
		{
			AnimInst->Montage_Play(AnimInst->HitMontage);
			AnimInst->Montage_JumpToSection(TEXT("Hit2"));
		}
		else if (HitType == EHitType::EHT_Charge)
		{
			if (BackHit(Hitter))
			{
				AnimInst->Montage_Play(AnimInst->StunMontage);
			}
			else
			{
				AnimInst->Montage_Play(AnimInst->HitMontage);
				AnimInst->Montage_JumpToSection(TEXT("Hit2"));
			}
		}
		else if (HitType == EHitType::EHT_Bullet)
		{
			if (Parriable)
			{
				AnimInst->Montage_Play(AnimInst->StunMontage);
			}
			else
			{
				AnimInst->Montage_Play(AnimInst->HitMontage);
				AnimInst->Montage_JumpToSection(TEXT("Hit1"));
			}
		}
	}
}

float ABBAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	GetAttribute()->ReceiveDamage(DamageAmount);
	HealthBarWidget->SetHealthPercent(GetAttribute()->GetHealthPercent());

	return DamageAmount;
}

void ABBAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInst = Cast<UBBAIAnimInstance>(GetMesh()->GetAnimInstance());
}

bool ABBAICharacter::BackHit(AActor* Hitter)
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
