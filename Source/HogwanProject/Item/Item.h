// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType
{
	EIT_None,
	EIT_Weapon,
	EIT_UseItem,
	EIT_Accessory,
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped,
	EIS_Stored,
};

UCLASS()
class HOGWANPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemType")
	EItemType ItemType = EItemType::EIT_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemType")
	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

	UFUNCTION()
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	UFUNCTION()
	void Equip(USceneComponent* InParent, FName InSocketName);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FORCEINLINE void SetOwner(AActor* _Owner) { Owner = _Owner; }
protected:
	virtual void BeginPlay() override;
	AActor* Owner = nullptr;

private:
};
