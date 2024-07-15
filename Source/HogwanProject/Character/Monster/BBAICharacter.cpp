// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/BBAICharacter.h"
#include "AI/BBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/BBEnum.h"
#include "Character/Monster/BBAIAnimInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Components/CapsuleComponent.h"

ABBAICharacter::ABBAICharacter()
{
	FrontTakeDownBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontTakeDownBox"));
	FrontTakeDownBox->SetupAttachment(GetRootComponent());

	BackTakeDownBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BackTakeDownBox"));
	BackTakeDownBox->SetupAttachment(GetRootComponent());
}

void ABBAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeathCheck();
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
		if (!BlackBoard)
		{
			return;
		}

		int32 ToughnessDegree = static_cast<int32>(Toughness);
		int32 HittypeDegree = static_cast<int32>(HitType);

		if (HitType == EHitType::EHT_Charge && CanGrabType)
		{
			if (BackHit(Hitter))
			{
				AnimInst->Montage_Play(AnimInst->BackStunMontage);
				BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Unable));
				return;
			}
		}

		if (HitType == EHitType::EHT_Bullet && CanGrabType)
		{
			if (Parriable)
			{
				AnimInst->Montage_Play(AnimInst->FrontStunMontage);
				BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Unable));
				Parriable = false;
				return;
			}
		}

		if (HittypeDegree >= ToughnessDegree && HittypeDegree <= (ToughnessDegree + 1))
		{
			if (BackHit(Hitter))
			{
				AnimInst->Montage_Play(AnimInst->BackHitMontage);
			}
			else
			{
				AnimInst->Montage_Play(AnimInst->FrontHitMontage);
			}

			AnimInst->Montage_JumpToSection(TEXT("Hit1"));
			BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Unable));
			return;
		}
		else if (HittypeDegree >= ToughnessDegree + 2)
		{
			if (BackHit(Hitter))
			{
				AnimInst->Montage_Play(AnimInst->BackHitMontage);
			}
			else
			{
				AnimInst->Montage_Play(AnimInst->FrontHitMontage);
			}
			AnimInst->Montage_JumpToSection(TEXT("Hit2"));
			BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Unable));
			return;
		}
	}
}

void ABBAICharacter::DeathCheck()
{
	if (!IsDeath && GetAttribute()->GetIsDeath() && !IsGrapped)
	{
		ABBAIController* Con = Cast<ABBAIController>(GetController());
		UBlackboardComponent* BlackBoard = Con->GetBlackboardComponent();
		if (BlackBoard)
		{
			BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Dead));
		}

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FrontTakeDownBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BackTakeDownBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HealthBarWidget->SetHiddenInGame(true);
		GetMesh()->SetSimulatePhysics(true);

		IsDeath = true;
	}
}

void ABBAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInst = Cast<UBBAIAnimInstance>(GetMesh()->GetAnimInstance());

	FrontTakeDownBox->OnComponentBeginOverlap.AddDynamic(this, &ABBAICharacter::FrontTakeDownBoxBeginOverlap);
	FrontTakeDownBox->OnComponentEndOverlap.AddDynamic(this, &ABBAICharacter::FrontTakeDownBoxEndOverlap);

	BackTakeDownBox->OnComponentBeginOverlap.AddDynamic(this, &ABBAICharacter::BackTakeDownBoxBeginOverlap);
	BackTakeDownBox->OnComponentEndOverlap.AddDynamic(this, &ABBAICharacter::BackTakeDownBoxEndOverlap);

	FrontTakeDownBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BackTakeDownBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
		Hunter->SetCanTakeDown(true);
	}
}

void ABBAICharacter::FrontTakeDownBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		Hunter->SetCanTakeDown(false);
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
		Hunter->SetCanTakeDown(true);
	}
}

void ABBAICharacter::BackTakeDownBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);

	if (Hunter)
	{
		Hunter->SetCanTakeDown(false);
	}
}
