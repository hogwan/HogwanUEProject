// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/InteractObject.h"
#include "Components/SphereComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Global/BBGameInstance.h"
#include "HUD/BBHUD.h"
#include "HUD/BBOverlay.h"
#include "Components/TextBlock.h"

AInteractObject::AInteractObject()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

}


void AInteractObject::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractObject::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AInteractObject::OnEndOverlap);
}

void AInteractObject::Interact()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	GameIns->RecentlyInteractObject = this;
}

void AInteractObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);
	if (Hunter)
	{
		Hunter->SetOverlappingObject(this);
		SetOwner(Hunter);

		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		ABBHUD* BBHUD = GameIns->HUD;
		UBBOverlay* BBOverlay = BBHUD->GetBBOverlay();

		BBOverlay->ItemInteractText->SetVisibility(ESlateVisibility::Visible);

	}
}

void AInteractObject::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHunter* Hunter = Cast<AHunter>(OtherActor);
	if (Hunter)
	{
		Hunter->SetOverlappingObject(nullptr);
		SetOwner(nullptr);

		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		ABBHUD* BBHUD = GameIns->HUD;
		UBBOverlay* BBOverlay = BBHUD->GetBBOverlay();

		BBOverlay->ItemInteractText->SetVisibility(ESlateVisibility::Hidden);
	}
}

