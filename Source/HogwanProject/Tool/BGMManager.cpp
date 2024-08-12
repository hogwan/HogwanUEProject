// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/BGMManager.h"
#include "Global/BBGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
ABGMManager::ABGMManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioCOmponent"));

}

// Called when the game starts or when spawned
void ABGMManager::BeginPlay()
{
	Super::BeginPlay();

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	GameIns->BGMManager = this;

	BGMChange(TEXT("Normal"));
	
}

// Called every frame
void ABGMManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABGMManager::BGMChange(FString _BGMName)
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	if (GameIns->BGMMap[_BGMName])
	{
		AudioComponent->SetSound(GameIns->BGMMap[_BGMName]);
		AudioComponent->Play();
	}
}

