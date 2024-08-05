// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Item/Item.h"
#include "Components/SphereComponent.h"
#include "Character/Hunter/Hunter.h"
#include "Global/BBGameInstance.h"
#include "HUD/BBHUD.h"
#include "HUD/BBOverlay.h"
#include "Components/TextBlock.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	Mesh->SetupAttachment(GetRootComponent());
}


// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 15.f, FColor::Cyan, TEXT("BeginOverlap"));
	}

	AHunter* Hunter= Cast<AHunter>(OtherActor);
	if (Hunter)
	{
		Hunter->SetOverlappingItem(this);

		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		ABBHUD* BBHUD = GameIns->HUD;
		UBBOverlay* BBOverlay = BBHUD->GetBBOverlay();

		BBOverlay->ItemInteractText->SetVisibility(ESlateVisibility::Visible);

	}
}

void AItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHunter* Hunter= Cast<AHunter>(OtherActor);
	if (Hunter && Hunter->GetOverlappingItem() == this)
	{
		Hunter->SetOverlappingItem(nullptr);

		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		ABBHUD* BBHUD = GameIns->HUD;
		UBBOverlay* BBOverlay = BBHUD->GetBBOverlay();

		BBOverlay->ItemInteractText->SetVisibility(ESlateVisibility::Hidden);
	}
}
