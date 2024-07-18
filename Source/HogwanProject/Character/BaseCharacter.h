// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class HOGWANPROJECT_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;

	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE class UAttributeComponent* GetAttribute() { return Attribute; }
	FORCEINLINE class UMotionWarpingComponent* GetMotionWarping() { return MotionWarping; }
protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAttributeComponent* Attribute;

	UPROPERTY(VisibleAnywhere)
	class UHealthBarComponent* HealthBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionWarpingComponent* MotionWarping;

	bool BackHit(AActor* Hitter);

	virtual void ResetState();

private:


};
