// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/BossRoomBox.h"
#include "Character/Monster/BBAICharacter.h"
#include "Global/BBGameInstance.h"
#include "Tool/BGMManager.h"
#include "Components/BoxComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Perception/PawnSensingComponent.h"
#include "Tool/FogDoor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/BBAIController.h"
#include "HUD/HealthBarComponent.h"

// Sets default values
ABossRoomBox::ABossRoomBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(BoxCol);
}

// Called when the game starts or when spawned
void ABossRoomBox::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCol->OnComponentBeginOverlap.AddDynamic(this, &ABossRoomBox::HunterCol);
}

// Called every frame
void ABossRoomBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CombatEnd();
}

void ABossRoomBox::BossDeathCheck()
{
	if (Boss->IsDeath)
	{
		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		GameIns->BGMManager->BGMChange(TEXT("Normal"));
	}
}

void ABossRoomBox::HunterCol(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);
	if (!IsHunterIn && Hunter)
	{
		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		GameIns->BGMManager->BGMChange(BGMName);

		for (ABBAICharacter* Monster : GameIns->AllMonsters)
		{
			if (Monster == nullptr) continue;
			Monster->PawnSensing->SetSensingUpdatesEnabled(false);
			Monster->PerceiveHunter = false;
			

			ABBAIController* Con = Cast<ABBAIController>(Monster->GetController());
			if (Con)
			{
				UBlackboardComponent* BlackBoard = Con->GetBlackboardComponent();

				BlackBoard->SetValueAsEnum(TEXT("StateValue"), static_cast<uint8>(EMonsterState::EMS_Idle));
				
				Monster->GetHealthBarWidget()->SetVisibility(false);
				Con->StopMovement();
			}
		}

		for (AFogDoor* Door : FogDoors)
		{
			Door->FogOn();
		}

		Boss->PerceiveHunter = true;
		IsHunterIn = true;
	}
}

void ABossRoomBox::CombatEnd()
{
	if (Boss->IsDeath)
	{
		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		GameIns->BGMManager->BGMChange(TEXT("Normal"));

		for (ABBAICharacter* Monster : GameIns->AllMonsters)
		{
			if (Monster == nullptr) continue;
			Monster->PawnSensing->SetSensingUpdatesEnabled(true);
		}

		for (AFogDoor* Door : FogDoors)
		{
			Door->FogOff();
		}

		Destroy();
	}
}
