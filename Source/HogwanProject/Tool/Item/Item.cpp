// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Item/Item.h"
#include "NiagaraComponent.h"
#include "Character/Hunter/Hunter.h"
#include "ActorComponent/InventoryComponent.h"
#include "Global/BBGameInstance.h"
#include "HUD/BBOverlay.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "HUD/ItemExplain.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Effect = CreateDefaultSubobject<UNiagaraComponent>("Effect");
	Effect->SetupAttachment(GetRootComponent());
}


void AItem::Interact()
{
	Super::Interact();

	AHunter* Hunter = Cast<AHunter>(GetOwner());
	if (Hunter == nullptr) return;

	if (Hunter->GetIsOpenItemExplain() == false)
	{
		Hunter->GetInventory()->PickUpItem(this);

		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());

		Hunter->GetBBOverlay()->ItemExplain->ItemExplainImage->SetBrushFromTexture(GameIns->EnumTextureMap[Item]);
		Hunter->GetBBOverlay()->ItemExplain->ItemExplainText->SetText(FText::FromString(GameIns->ItemExplain[Item]));
		Hunter->GetBBOverlay()->ItemExplain->ItemExplainNum->SetText(FText::FromString(FString::FromInt(GetItemNum())));

		Hunter->SetOverlappingObject(nullptr);
		Hunter->SetIsOpenItemExplain(true);
		Hunter->UseItemSlotUpdate();
		Hunter->PotionBulletUpdate();
		Hunter->GetBBOverlay()->ItemExplain->SetVisibility(ESlateVisibility::Visible);

		Destroy();
	}
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
