// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossRoomBox.generated.h"

UCLASS()
class HOGWANPROJECT_API ABossRoomBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossRoomBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCol;

	UPROPERTY(EditAnywhere)
	class ABBAICharacter* Boss = nullptr;

	UPROPERTY(EditAnywhere)
	FString BGMName = "None";

	bool IsHunterIn = false;

	void BossDeathCheck();

	UFUNCTION()
	void HunterCol(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void CombatEnd();

};
