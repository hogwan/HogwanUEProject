// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBAICharacter.h"
#include "AI/BBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/BBEnum.h"
#include "AI/BBAIAnimInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Character/Hunter/Hunter.h"

ABBAICharacter::ABBAICharacter()
{
	FrontTakeDownBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontTakeDownBox"));
	FrontTakeDownBox->SetupAttachment(GetRootComponent());

	BackTakeDownBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BackTakeDownBox"));
	BackTakeDownBox->SetupAttachment(GetRootComponent());
}

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

	FrontTakeDownBox->OnComponentBeginOverlap.AddDynamic(this, &ABBAICharacter::FrontTakeDownBoxBeginOverlap);
	FrontTakeDownBox->OnComponentEndOverlap.AddDynamic(this, &ABBAICharacter::FrontTakeDownBoxEndOverlap);

	BackTakeDownBox->OnComponentBeginOverlap.AddDynamic(this, &ABBAICharacter::BackTakeDownBoxBeginOverlap);
	BackTakeDownBox->OnComponentEndOverlap.AddDynamic(this, &ABBAICharacter::BackTakeDownBoxEndOverlap);
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

void ABBAICharacter::FrontTakeDownBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		FVector HunterLocation = Hunter->GetActorLocation();
		HunterLocation.Z = 0.f;

		FVector ActorLocation = GetActorLocation();
		ActorLocation.Z = 0.f;

		FRotator FindRotation = UKismetMathLibrary::FindLookAtRotation(HunterLocation, ActorLocation);

		Hunter->SetTakeDownInfo(this, FrontTakeDownBox->GetComponentLocation(), FindRotation);
		Hunter->bCanTakeDown = true;
	}
}

void ABBAICharacter::FrontTakeDownBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		Hunter->bCanTakeDown = false;
	}
}

void ABBAICharacter::BackTakeDownBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		FVector HunterLocation = Hunter->GetActorLocation();
		HunterLocation.Z = 0.f;

		FVector ActorLocation = GetActorLocation();
		ActorLocation.Z = 0.f;

		FRotator FindRotation = UKismetMathLibrary::FindLookAtRotation(HunterLocation, ActorLocation);

		Hunter->SetTakeDownInfo(this, BackTakeDownBox->GetComponentLocation(), FindRotation);
		Hunter->bCanTakeDown = true;
	}
}

void ABBAICharacter::BackTakeDownBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		Hunter->bCanTakeDown = false;
	}
}
