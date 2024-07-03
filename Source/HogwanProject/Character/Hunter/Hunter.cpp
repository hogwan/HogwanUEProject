// Fill out your copyright notice in the Description page of Project Settings.


#include "Hunter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Global/BBGameInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/Monster/Monster.h"

// Sets default values
AHunter::AHunter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 250.f;
	SpringArm->SetRelativeRotation(FRotator(25.f, 0.f, 0.f));

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);
}

void AHunter::BeginPlay()
{
	Super::BeginPlay();

}

void AHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceLockOnTarget(DeltaTime);
}

void AHunter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHunter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AHunter::MoveEnd);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHunter::Look);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AHunter::Run);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AHunter::Dodge);
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Started, this, &AHunter::LockOn);
		EnhancedInputComponent->BindAction(AttackAction,
			ETriggerEvent::Started, this, &AHunter::Attack);
		EnhancedInputComponent->BindAction(InteractAction,
			ETriggerEvent::Started, this, &AHunter::Interact);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AHunter::Shoot);
		
	}

}

void AHunter::Move(const FInputActionValue& Value)
{
	InputVector = FVector(Value.Get<FVector2D>().X, Value.Get<FVector2D>().Y, 0.f);

	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;

	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputVector.Y);
	AddMovementInput(RightDirection, InputVector.X);

	FVector MoveVector = GetActorForwardVector() * InputVector.Y + GetActorRightVector() * InputVector.X;
	ForwardDirection.Normalize();
	MoveVector.Normalize();
	float Degree = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardDirection, MoveVector)));

	if (InputVector.X < 0.f)
	{
		MoveRotDegree = -Degree;
	}
	else
	{
		MoveRotDegree = Degree;
	}
}

void AHunter::MoveEnd(const FInputActionValue& Value)
{
	InputVector = FVector::Zero();
}

void AHunter::Look(const FInputActionValue& Value)
{
	if (bIsLockOn) return;

	const FVector2D MouseVector = Value.Get<FVector2D>();

	AddControllerYawInput(MouseVector.X);
	AddControllerPitchInput(-MouseVector.Y);
}

void AHunter::Run(const FInputActionValue& Value)
{
	bIsRun = true;
   	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AHunter::Dodge(const FInputActionValue& Value)
{
	if (!bIsRun)
	{
		if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

			if (bIsLockOn && AnimInstance && DodgeMontage)
			{
				AnimInstance->Montage_Play(DodgeMontage);
				CurActionState = ECharacterActionState::ECAS_Dodging;

				FRotator Rotation = GetControlRotation();
				FRotator YawRotation(0.f, Rotation.Yaw, 0.f);


				FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
				FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

				FVector DirectionVector = ForwardDirection * InputVector.Y + RightDirection * InputVector.X;

				if (InputVector.IsNearlyZero() == false)
				{
					FRotator OriginalRot = GetActorRotation();
					FRotator SettingRot = FRotator(OriginalRot.Pitch, Rotation.Yaw, OriginalRot.Roll);
					SetActorRotation(SettingRot);
				}

				DirectionVector.Normalize();
				ForwardDirection.Normalize();
				float Degree = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardDirection, DirectionVector)));

				if (InputVector.X < 0.f)
				{
					Degree *= -1.f;
				}


				FName Section = FName("DodgeBack");

				if (InputVector.IsNearlyZero() == false)
				{
					if (Degree >= 45.f && Degree <= 135.f)
					{
						Section = FName("DodgeRight");
					}
					else if (Degree > -45.f && Degree < 45.f)
					{
						Section = FName("DodgeForward");
					}
					else if (Degree >= -135.f && Degree <= -45.f)
					{
						Section = FName("DodgeLeft");
					}
				}

				AnimInstance->Montage_JumpToSection(Section, DodgeMontage);

			}
			else
			{
				AnimInstance->Montage_Play(RollMontage);
				CurActionState = ECharacterActionState::ECAS_Dodging;
			}
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	bIsRun = false;
}

void AHunter::LockOn(const FInputActionValue& Value)
{
	if (bIsLockOn)
	{
		ReleaseLockOn();
		return;
	}

	FVector CameraForwardVector = ViewCamera->GetForwardVector();
	FVector CurPos = GetActorLocation() + CameraForwardVector * 700.f;
	FVector TargetPos = CurPos + CameraForwardVector * 800.f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Emplace(EObjectTypeQuery::ObjectTypeQuery8);

	TArray<AActor*, FDefaultAllocator> IgnoredActors;
	IgnoredActors.Emplace(this);

	FHitResult OutHit;

	bool bhit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		CurPos,
		TargetPos,
		700.f,
		ObjectTypesArray,
		false,
		IgnoredActors,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true
	);

	if (bhit == false)
	{
		return;
	}

	AMonster* Monster = Cast<AMonster>(OutHit.GetActor());
	if (Monster)
	{
		if (Monster->GetAttribute()->GetIsDeath())
		{
			return;
		}


		SetLockOn(Monster);
	}

}

void AHunter::Attack(const FInputActionValue& Value)
{
	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && AttackMontage)
		{
			CurActionState = ECharacterActionState::ECAS_Attacking;
			AnimInstance->Montage_Play(AttackMontage);
			AnimInstance->Montage_JumpToSection("Attack1");
		}
		return;
	}

	if (CurActionState == ECharacterActionState::ECAS_Attacking
		&& NextAttackChance == true)
	{
		GoNextAttack = true;
		return;
	}
}

void AHunter::Interact(const FInputActionValue& Value)
{

}

void AHunter::Shoot(const FInputActionValue& Value)
{
	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && ShootMontage)
		{
			CurActionState = ECharacterActionState::ECAS_Attacking;
			AnimInstance->Montage_Play(ShootMontage);
		}
	}
}

void AHunter::TraceLockOnTarget(float DeltaTime)
{
	if (LockOnTarget)
	{
		AMonster* Monster = Cast<AMonster>(LockOnTarget);
		if (Monster->GetAttribute()->GetIsDeath())
		{
			ReleaseLockOn();
		}

		FVector Start = GetActorLocation();
		FVector Target = LockOnTarget->GetActorLocation();

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
		FRotator StartRotation = GetController()->GetControlRotation();
		FRotator Result = UKismetMathLibrary::RInterpTo(StartRotation, TargetRotation, DeltaTime, 5.f);

		FRotator CameraRotation = FRotator(-25.f, Result.Yaw, 0.f);

		GetController()->SetControlRotation(CameraRotation);
		
		if (!bIsRun)
		{
			GetCharacterMovement()->bOrientRotationToMovement = false;
			SetActorRotation(FRotator(0.f, Result.Yaw, 0.f));
		}
		else
		{
			GetCharacterMovement()->bOrientRotationToMovement = true;
		}
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AHunter::ReleaseLockOn()
{
	bIsLockOn = false;
	if (LockOnTarget)
	{
		LockOnTarget = nullptr;
	}

	UBBGameInstance* GameInstance = Cast<UBBGameInstance>(GetGameInstance());

	if (GameInstance && GameInstance->LockOnTarget)
	{
		AMonster* Monster = Cast<AMonster>(GameInstance->LockOnTarget);

		if (Monster)
		{
			Monster->GetLockOnWidget()->SetVisibility(false);
		}

		GameInstance->LockOnTarget = nullptr;
	}
}

void AHunter::SetLockOn(AMonster* Target)
{
	bIsLockOn = true;
	LockOnTarget = Target;

	Target->GetLockOnWidget()->SetVisibility(true);

	UBBGameInstance* GameInstance = Cast<UBBGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		GameInstance->LockOnTarget = Target;
	}
}
