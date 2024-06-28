// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "Monster.generated.h"

UCLASS()
class HOGWANPROJECT_API AMonster : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void GetHit(FVector ImpactPoint) override;
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE class UAttributeComponent* GetAttribute() { return Attribute; }

	FORCEINLINE class UWidgetComponent* GetLockOnWidget() { return LockOnTargetWidget; }
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* LockOnTargetWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAttributeComponent* Attribute;

};
