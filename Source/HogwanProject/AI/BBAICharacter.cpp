// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBAICharacter.h"
#include "AI/BBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/BBEnum.h"
#include "AI/BBAIAnimInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"


ABBAIController* ABBAICharacter::GetBBAIController()
{
	AController* Con = GetController();

	return Cast<ABBAIController>(GetController());
}

void ABBAICharacter::GetHit(const FVector& ImpactPoint)
{
	Super::GetHit(ImpactPoint);

	ABBAIController* Con = Cast<ABBAIController>(GetController());
	int StateValue = 10;
	
	if (Con && StateValue)
	{
		UBlackboardComponent* BlackBoard = Con->GetBlackboardComponent();
		if (BlackBoard)
		{
			BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Unable));
			StateValue = static_cast<int>(BlackBoard->GetValueAsEnum(TEXT("StateValue")));
		}
	}

	if (AnimInst)
	{
		AnimInst->Montage_Play(AnimInst->HitMontage);

		int Random = FMath::RandRange(0, 1);

		switch (Random)
		{
		case 0:
			AnimInst->Montage_JumpToSection(TEXT("Hit1"));
			break;
		case 1:
			AnimInst->Montage_JumpToSection(TEXT("Hit2"));
			break;
		default:
			break;
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
