// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/HitInterface.h"
#include "Monster.generated.h"

UCLASS()
class HOGWANPROJECT_API AMonster : public APawn, public IHitInterface
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void GetHit() override;

	FORCEINLINE class USkeletalMeshComponent* GetMesh() { return Mesh; }
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* Capsule;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Arrow;
};
