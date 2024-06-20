// Fill out your copyright notice in the Description page of Project Settings.


#include "Hunter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Item/Weapon/Weapon.h"

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

// Called when the game starts or when spawned
void AHunter::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceLockOnTarget(DeltaTime);
}

// Called to bind functionality to input
void AHunter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHunter::Move);
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
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;

	FVector InputMoveVector = FVector(Value.Get<FVector2D>().X, Value.Get<FVector2D>().Y, 0.f);

	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputMoveVector.Y);
	AddMovementInput(RightDirection, InputMoveVector.X);

	FVector MoveVector = GetActorForwardVector() * InputMoveVector.Y + GetActorRightVector() * InputMoveVector.X;
	ForwardDirection.Normalize();
	MoveVector.Normalize();
	float Degree = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardDirection, MoveVector)));

	if (InputMoveVector.X < 0.f)
	{
		MoveRotDegree = -Degree;
	}
	else
	{
		MoveRotDegree = Degree;
	}
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

	}

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	bIsRun = false;
}

void AHunter::LockOn(const FInputActionValue& Value)
{
	if (bIsLockOn)
	{
		bIsLockOn = false;
		if (LockOnTarget)
		{
			LockOnTarget = nullptr;
		}

		return;
	}

	FVector CameraForwardVector = ViewCamera->GetForwardVector();
	FVector CurPos = GetActorLocation() + CameraForwardVector * 700.f;
	FVector TargetPos = CurPos + CameraForwardVector * 800.f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Reserve(1);
	ObjectTypesArray.Emplace(ECollisionChannel::ECC_Pawn);

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

	LockOnTarget = OutHit.GetActor();
	bIsLockOn = true;
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
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		EEquipHand EquipHand = OverlappingWeapon->EquipHand;

		if (EquipHand == EEquipHand::EEH_RightHand)
		{
			OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
			CurWeaponState = ECharacterWeaponState::ECWS_OnehandedWeapon;
			OverlappingItem = nullptr;
			RightHandWeapon = OverlappingWeapon;
		}
		else if (EquipHand == EEquipHand::EEH_LeftHand)
		{
			OverlappingWeapon->Equip(GetMesh(), FName("LeftHandSocket"));
			CurGunState = ECharacterGunState::ECGS_Equiped;
			OverlappingItem = nullptr;
			LeftHandWeapon = OverlappingWeapon;
		}
		OverlappingWeapon->SetOwner(this);
	}
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
		FVector Start = GetActorLocation();
		FVector Target = LockOnTarget->GetActorLocation();

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
		FRotator StartRotation = GetController()->GetControlRotation();
		FRotator Result = UKismetMathLibrary::RInterpTo(StartRotation, TargetRotation, DeltaTime, 5.f);

		GetController()->SetControlRotation(Result);
		
		if (!bIsRun)
		{
			GetCharacterMovement()->bOrientRotationToMovement = false;
			SetActorRotation(Result);
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
