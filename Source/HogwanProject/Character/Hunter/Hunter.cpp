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
#include "Character/Monster/BBAICharacter.h"
#include "Character/Monster/BBAIAnimInstance.h"
#include "Weapon/MeleeWeapon.h"
#include "Weapon/RangedWeapon.h"
#include "Global/BBGameInstance.h"
#include "HUD/BBHUD.h"
#include "HUD/BBOverlay.h"
#include "ActorComponent/InventoryComponent.h"
#include "Character/Hunter/BBPlayerController.h"
#include "Tool/Item/Item.h"
#include "HUD/BBStatusInventory.h"
#include "Components/TextBlock.h"
#include "Projectile/ThrowObject.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CanvasPanel.h"
#include "HUD/ItemExplain.h"
#include "Components/Image.h"
#include "Tool/InteractObject.h"
#include "Tool/Lantern/Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/ProgressBar.h"
#include "Tool/BGMManager.h"

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

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	for (int i = 0; i < 3; i++)
	{
		RightHandSlotData.Add(nullptr);
		LeftHandSlotData.Add(nullptr);
		UseItemSlotData.Add(nullptr);
	}
}

void AHunter::BeginPlay()
{
	Super::BeginPlay();

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	GameIns->Hunter = this;

	APlayerController* BBPlayerController = Cast<APlayerController>(GetController());
	GameIns->HUD = Cast<ABBHUD>(BBPlayerController->GetHUD());

	BBOverlay = GameIns->HUD->GetBBOverlay();

	EquipWeapon(MeleeWeaponsInPocket[0]);
	EquipWeapon(RangedWeaponsInPocket[0]);
	UseItemSlotUpdate();
	
	StatusUpdate();
	GetAttribute()->Hp = GetAttribute()->MaxHp;
	GetAttribute()->RegainHp = GetAttribute()->MaxHp;
	GetAttribute()->Stamina = GetAttribute()->MaxStamina;
}

void AHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeathCheck();
	TraceLockOnTarget(DeltaTime);
	StaminaUpdate(DeltaTime);
	DisplayGoldUpdate(DeltaTime);
	UpdateOverlay();
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
		EnhancedInputComponent->BindAction(ChargeAttackAction,
			ETriggerEvent::Started, this, &AHunter::ChargeAttack);
		EnhancedInputComponent->BindAction(InteractAction,
			ETriggerEvent::Started, this, &AHunter::Interact);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AHunter::Shoot);
		EnhancedInputComponent->BindAction(MeleeWeaponSwapAction,
			ETriggerEvent::Started, this, &AHunter::MeleeWeaponSwap);
		EnhancedInputComponent->BindAction(RangedWeaponSwapAction, ETriggerEvent::Started, this, &AHunter::RangedWeaponSwap);
		EnhancedInputComponent->BindAction(DeformWeaponAction, ETriggerEvent::Started, this, &AHunter::DeformWeapon);
		EnhancedInputComponent->BindAction(OpenStatusInventoryAction, ETriggerEvent::Started, this, &AHunter::OpenStatusInventory);
		EnhancedInputComponent->BindAction(OpenQuickSlotAction, ETriggerEvent::Started, this, &AHunter::OpenQuickSlot);
		EnhancedInputComponent->BindAction(UseItemSwapAction, ETriggerEvent::Started, this, &AHunter::ItemSwap);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &AHunter::Throw);
		EnhancedInputComponent->BindAction(DrinkAction, ETriggerEvent::Started, this, &AHunter::Drink);
		
	}

}

void AHunter::GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType)
{
	Super::GetHit(ImpactPoint, Hitter, HitType);

	CurActionState = ECharacterActionState::ECAS_Hit;

	UBBAnimInstance* AnimInst = Cast<UBBAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInst)
	{
		if (BackHit(Hitter))
		{
			AnimInst->Montage_Play(MontageMap[TEXT("BackHit")]);
		}
		else
		{
			AnimInst->Montage_Play(MontageMap[TEXT("FrontHit")]);
		}

		switch (HitType)
		{
		case EHitType::EHT_Light:
		{
			if (BackHit(Hitter))
			{
				AnimInst->Montage_JumpToSection(TEXT("BackHit1"));
			}
			else
			{
				AnimInst->Montage_JumpToSection(TEXT("FrontHit1"));
			}
		}
			break;
		case EHitType::EHT_Heavy:
		{
			if (BackHit(Hitter))
			{
				AnimInst->Montage_JumpToSection(TEXT("BackHit2"));
			}
			else
			{
				AnimInst->Montage_JumpToSection(TEXT("FrontHit2"));
			}
		}
			break;
		case EHitType::EHT_Charge:
		{
			if (BackHit(Hitter))
			{
				AnimInst->Montage_JumpToSection(TEXT("BackHit2"));
			}
			else
			{
				AnimInst->Montage_JumpToSection(TEXT("FrontHit3"));
			}
		}
			break;
		}
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
	if (bExhaust) return;

	bIsRun = true;
   	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AHunter::Dodge(const FInputActionValue& Value)
{
	if (bExhaust) return;

	ConsumeStaminaAmount = BaseConsumeStamina;

	if (!bIsRun)
	{
		if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

			if (AnimInstance == nullptr) return;
			GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			if (bIsLockOn)
			{
				FString MontageName;
				MontageName += GetWeaponStateToString(CurWeaponState);

				if (CurWeaponState == ECharacterWeaponState::ECWS_TwohandedWeapon)
				{
					MontageName += EquippedMeleeWeapon->GetName();
				}

				MontageName += TEXT("Dodge");

				AnimInstance->Montage_Play(MontageMap[MontageName]);

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

				AnimInstance->Montage_JumpToSection(Section, MontageMap[MontageName]);

			}
			else
			{
				FString MontageName;
				MontageName += GetWeaponStateToString(CurWeaponState);
				if (CurWeaponState == ECharacterWeaponState::ECWS_TwohandedWeapon)
				{
					MontageName += EquippedMeleeWeapon->GetName();
				}
				MontageName += TEXT("Roll");

				AnimInstance->Montage_Play(MontageMap[MontageName]);
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

	TArray<FHitResult> OutHits;

	bool bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		CurPos,
		TargetPos,
		700.f,
		ObjectTypesArray,
		false,
		IgnoredActors,
		EDrawDebugTrace::None,
		OutHits,
		true
	);

	if (bhit == false)
	{
		return;
	}

	for (const FHitResult& Result : OutHits)
	{
		ABBAICharacter* Monster = Cast<ABBAICharacter>(Result.GetActor());

		if (Monster)
		{
			if (Monster->GetAttribute()->GetIsDeath())
			{
				continue;
			}


			SetLockOn(Monster);
			return;
		}
	}
}

void AHunter::Attack(const FInputActionValue& Value)
{
	if (bExhaust) return;

	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && EquippedMeleeWeapon && bCanTakeDown && MontageMap[TEXT("TakeDown")])
		{
			SetActorLocation(TakeDownPos);

			SetActorRotation(TakeDownRot);

			GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			CurActionState = ECharacterActionState::ECAS_TakeDown;
			ConsumeStaminaAmount = BaseConsumeStamina * 0.5f;

			switch (EquippedMeleeWeapon->Weapon)
			{
			case EWeapon::EW_GreatSword_Deformed:
				AnimInstance->Montage_Play(MontageMap[TEXT("TwoHanded_GreatSword_TakeDown")]);
				break;
			case EWeapon::EW_Katana_Deformed:
				AnimInstance->Montage_Play(MontageMap[TEXT("TwoHanded_Katana_TakeDown")]);
				break;
			default:
				AnimInstance->Montage_Play(MontageMap[TEXT("TakeDown")]);
				break;
			}

			ABBAICharacter* Monster = Cast<ABBAICharacter>(TakeDownTarget);

			Monster->IsGrapped = true;

			if (Monster)
			{
				UBBAIAnimInstance* MonsterAnim = Monster->GetBBAIAnimInstance();

				if (MonsterAnim)
				{
					FVector MonsterForward = Monster->GetActorForwardVector();
					MonsterForward.Z = 0.f;

					FVector MonsterToPlayer = GetActorLocation() - Monster->GetActorLocation();
					MonsterToPlayer.Z = 0.f;

					MonsterForward.Normalize();
					MonsterToPlayer.Normalize();

					float DotScala = UKismetMathLibrary::Dot_VectorVector(MonsterForward, MonsterToPlayer);

					float RadianAngle = UKismetMathLibrary::Acos(DotScala);

					float DegreeAngle = FMath::RadiansToDegrees(RadianAngle);
					
					if (DegreeAngle > 90.f)
					{
						Monster->AddActorWorldRotation(FRotator(0.f, 180.f, 0.f));
					}

					switch (EquippedMeleeWeapon->Weapon)
					{
					case EWeapon::EW_GreatSword_Deformed:
						MonsterAnim->Montage_Play(MonsterAnim->GreatSwordTakeDown);
						break;
					case EWeapon::EW_Katana_Deformed:
						MonsterAnim->Montage_Play(MonsterAnim->KatanaTakeDown);
						break;
					default:
						MonsterAnim->Montage_Play(MonsterAnim->NormalTakeDown);
						break;
					}
				}
			}


			return;
		}

		if (AnimInstance && EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->HitType = EHitType::EHT_Light;
			ConsumeStaminaAmount = BaseConsumeStamina;

			if (EquippedMeleeWeapon->Weapon == EWeapon::EW_GreatSword_Deformed)
			{
				EquippedMeleeWeapon->HitType = EHitType::EHT_Heavy;
				ConsumeStaminaAmount = BaseConsumeStamina * 1.5f;
			}

			CurActionState = ECharacterActionState::ECAS_Attacking;
			
			FString MontageName;
			MontageName += GetWeaponStateToString(CurWeaponState);
			if (CurWeaponState == ECharacterWeaponState::ECWS_TwohandedWeapon)
			{
				MontageName += EquippedMeleeWeapon->GetName();
			}
			MontageName += TEXT("Attack");

			if (MontageMap.Contains(MontageName))
			{
				UAnimMontage* Montage = MontageMap[MontageName];

				AnimInstance->Montage_Play(MontageMap[MontageName]);


			}
			return;
		}
	}

	if (CurActionState == ECharacterActionState::ECAS_Attacking
		&& NextAttackChance == true)
	{
		GoNextAttack = true;
		return;
	}
}

void AHunter::ChargeAttack(const FInputActionValue& Value)
{
	if (bExhaust) return;

	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->HitType = EHitType::EHT_Charge;
			CurActionState = ECharacterActionState::ECAS_Attacking;
			
			FString MontageName;
			MontageName += GetWeaponStateToString(CurWeaponState);
			if (CurWeaponState == ECharacterWeaponState::ECWS_TwohandedWeapon)
			{
				MontageName += EquippedMeleeWeapon->GetName();
			}
			MontageName += TEXT("ChargeAttack");

			AnimInstance->Montage_Play(MontageMap[MontageName]);
		}
		return;
	}
}

void AHunter::Interact(const FInputActionValue& Value)
{
	if (IsOpenItemExplain)
	{
		BBOverlay->ItemExplain->SetVisibility(ESlateVisibility::Hidden);
		IsOpenItemExplain = false;
		return;
	}

	if (OverlappingObject)
	{
		OverlappingObject->Interact();
	}

	
	
}

void AHunter::Shoot(const FInputActionValue& Value)
{
	if (CurWeaponState == ECharacterWeaponState::ECWS_TwohandedWeapon) return;
	if (GetBulletNum() == 0) return;

	if (EquippedRangedWeapon->WeaponType != EWeaponType::EWT_RangedWeapon) return;

	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && MontageMap[TEXT("Shoot")])
		{
			CurActionState = ECharacterActionState::ECAS_Attacking;
			AnimInstance->Montage_Play(MontageMap[TEXT("Shoot")]);
		}
	}
}

void AHunter::MeleeWeaponSwap(const FInputActionValue& Value)
{
	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && MontageMap[TEXT("MeleeWeaponSwap")])
		{
			CurActionState = ECharacterActionState::ECAS_WeaponSwaping;
			AnimInstance->Montage_Play(MontageMap[TEXT("MeleeWeaponSwap")]);
		}
	}

}

void AHunter::RangedWeaponSwap(const FInputActionValue& Value)
{
	if (CurWeaponState == ECharacterWeaponState::ECWS_TwohandedWeapon) return;

	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && MontageMap[TEXT("RangedWeaponSwap")])
		{
			CurActionState = ECharacterActionState::ECAS_WeaponSwaping;
			AnimInstance->Montage_Play(MontageMap[TEXT("RangedWeaponSwap")]);
		}
	}

}

void AHunter::ItemSwap(const FInputActionValue& Value)
{
	CurUseItemListNum++;

	if (CurUseItemListNum > MaxListNum) return;
	if (CurUseItemListNum == MaxListNum) CurUseItemListNum = 0;

	UseItemSlotUpdate();
}

void AHunter::DeformWeapon(const FInputActionValue& Value)
{
	if (MeleeWeaponsInPocket[CurMeleeListNum] == EWeapon::EW_RightFist) return;
	if (CurActionState == ECharacterActionState::ECAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		FString MontageName = GetDeformMontageName();

		if (EquippedMeleeWeapon->Weapon == EWeapon::EW_Katana)
		{
			Deform();
		}
		else if (EquippedMeleeWeapon->Weapon == EWeapon::EW_Katana_Deformed)
		{
			Deform();
		}
		else if (AnimInstance && MontageMap[MontageName])
		{
			CurActionState = ECharacterActionState::ECAS_Deform;
			AnimInstance->Montage_Play(MontageMap[MontageName]);
		}
	}
}

void AHunter::OpenStatusInventory(const FInputActionValue& Value)
{
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;

	ABBPlayerController* BBController = Cast<ABBPlayerController>(GetController());

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;
	BBHUD->GetBBStatusInventory()->WidgetUpdate();

	BBController->OpenWidget(EInputMode::StatusInventory);

	UGameplayStatics::PlaySound2D(
		this,
		GameIns->SoundMap["UIMenuOpen"]
	);
}

void AHunter::OpenQuickSlot(const FInputActionValue& Value)
{
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;

	ABBPlayerController* BBController = Cast<ABBPlayerController>(GetController());
	BBController->OpenWidget(EInputMode::QuickSlot);

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	UGameplayStatics::PlaySound2D(
		this,
		GameIns->SoundMap["UIMenuOpen"]
	);
}

void AHunter::PushDoor()
{
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(MontageMap[TEXT("PushDoor")]);
		CurActionState = ECharacterActionState::ECAS_PushDoor;
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AHunter::TurnOnLantern()
{
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(MontageMap[TEXT("TurnOnLantern")]);
		CurActionState = ECharacterActionState::ECAS_TurnOn;
	}
}

void AHunter::LanternOn()
{
	ALantern* Lantern = Cast<ALantern>(OverlappingObject);

	if (Lantern)
	{
		Lantern->TurnOn();
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());

	if (GameIns->SoundMap["LanternOn"])
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			GameIns->SoundMap["LanternOn"],
			Lantern->GetActorLocation()
		);
	}

	GameIns->LeastLantern = Lantern;
}

void AHunter::SitComplete()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(MontageMap[TEXT("Sitting")]);
	}

	ABBPlayerController* PlayerController = Cast<ABBPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->OpenWidget(EInputMode::LevelUp);
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	GameIns->ResetAllMonster();
}

void AHunter::SitDown()
{
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(MontageMap[TEXT("StandToSit")]);
		CurActionState = ECharacterActionState::ECAS_Sit;
	}
}

void AHunter::StandUp()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(MontageMap[TEXT("SitToStand")]);
	}
}


FString AHunter::GetDeformMontageName()
{
	FString MontageName = FString("None");

	if (EquippedMeleeWeapon)
	{
		switch (EquippedMeleeWeapon->Weapon)
		{
		case EWeapon::EW_SawCleaver:
			MontageName = FString("SawCleaver_Deform");
			break;
		case EWeapon::EW_SawCleaver_Deformed:
			MontageName = FString("SawCleaver_UnDeform");
			break;
		case EWeapon::EW_GreatSword:
			MontageName = FString("GreatSword_Deform");
			break;
		case EWeapon::EW_GreatSword_Deformed:
			MontageName = FString("GreatSword_UnDeform");
			break;
		case EWeapon::EW_Katana:
			MontageName = FString("Katana_Deform");
			break;
		case EWeapon::EW_Katana_Deformed:
			MontageName = FString("Katana_UnDeform");
			break;
		default:
			break;
		}
	}

	return MontageName;
}

void AHunter::TraceLockOnTarget(float DeltaTime)
{
	if (LockOnTarget)
	{
		ABBAICharacter* Monster = Cast<ABBAICharacter>(LockOnTarget);
		if (Monster->GetAttribute()->GetIsDeath())
		{
			ReleaseLockOn();
			return;
		}

		FVector Start = GetActorLocation();
		FVector Target = LockOnTarget->GetActorLocation();

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
		FRotator StartRotation = GetController()->GetControlRotation();
		FRotator Result = UKismetMathLibrary::RInterpTo(StartRotation, TargetRotation, DeltaTime, 5.f);

		FRotator SpringArmRotation = FRotator(-20.f, Result.Yaw, 0.f);

		GetController()->SetControlRotation(SpringArmRotation);

		FRotator CameraTarget = UKismetMathLibrary::FindLookAtRotation(ViewCamera->GetComponentLocation(), Target);
		FRotator CameraResult = UKismetMathLibrary::RInterpTo(ViewCamera->GetComponentRotation(), CameraTarget, DeltaTime, 5.f);

		ViewCamera->SetWorldRotation(CameraResult);
		
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
		SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
		ViewCamera->SetRelativeRotation(FRotator::ZeroRotator);
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
		ABBAICharacter* Monster = Cast<ABBAICharacter>(GameInstance->LockOnTarget);

		if (Monster)
		{
			Monster->GetLockOnWidget()->SetVisibility(false);
		}

		GameInstance->LockOnTarget = nullptr;
	}
}

void AHunter::SetLockOn(ABBAICharacter* Target)
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

void AHunter::Deform()
{
	if (EquippedMeleeWeapon)
	{
		switch (EquippedMeleeWeapon->Weapon)
		{
		case EWeapon::EW_SawCleaver:
			EquipWeapon(EWeapon::EW_SawCleaver_Deformed);
			break;
		case EWeapon::EW_SawCleaver_Deformed:
			EquipWeapon(EWeapon::EW_SawCleaver);
			break;
		case EWeapon::EW_GreatSword:
			EquipWeapon(EWeapon::EW_GreatSword_Deformed);
			break;
		case EWeapon::EW_GreatSword_Deformed:
			EquipWeapon(EWeapon::EW_GreatSword);
			break;
		case EWeapon::EW_Katana:
			EquipWeapon(EWeapon::EW_Katana_Deformed);
			break;
		case EWeapon::EW_Katana_Deformed:
			EquipWeapon(EWeapon::EW_Katana);
			break;
		default:
			break;
		}
	}
}

void AHunter::SetTakeDownInfo(AActor* Target, const FVector& Pos, const FRotator& Rot)
{
	TakeDownTarget = Target;
	TakeDownPos = Pos;
	TakeDownRot = Rot;
}


void AHunter::UpdateOverlay()
{
	BBOverlay->SetMaxHealthBarPercent(Attribute->GetHunterMaxHealthPercent());
	BBOverlay->SetHealthBarPercent(Attribute->GetHunterHealthPercent());
	BBOverlay->SetRegainHealthBarPercent(Attribute->GetHunterRegainHealthPercent());
	BBOverlay->SetMaxStaminaBarPerent(Attribute->GetHunterMaxStaminaPercent());
	BBOverlay->SetStaminaBarPercent(Attribute->GetHunterStaminaPercent());
	BBOverlay->Gold->SetText(FText::FromString(FString::FromInt(CurStatus.DisplayGold)));
}

void AHunter::Revive()
{
	Reset();

	GetAttribute()->Hp = GetAttribute()->MaxHp;

	GetAttribute()->Stamina = GetAttribute()->MaxStamina;

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	if (GameIns)
	{
		GameIns->ResetAllMonster();
		GameIns->ResetAllBoss();

		GetBBOverlay()->BossName->SetVisibility(ESlateVisibility::Hidden);
		GetBBOverlay()->BossHealthBar->SetVisibility(ESlateVisibility::Hidden);

		GameIns->BGMManager->BGMChange(TEXT("Normal"));

		ALantern* Lantern = GameIns->LeastLantern;
		if (Lantern)
		{
			SetActorLocation(Lantern->GetActorLocation() + Lantern->GetActorForwardVector() * 100.f);
		}
	}
}

void AHunter::DeathCheck()
{
	if (GetAttribute()->Hp <= 0.f && IsDeath == false)
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		IsDeath = true;
		ReleaseLockOn();

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(MontageMap[TEXT("Death")]);
			CurActionState = ECharacterActionState::ECAS_Death;
		}

	}
}

void AHunter::Death()
{
	ABBPlayerController* PlayerController = Cast<ABBPlayerController>(GetController());
	PlayerController->OpenWidget(EInputMode::Death);
}

void AHunter::Reset()
{
	CurActionState = ECharacterActionState::ECAS_Unoccupied;

	bIsRun = false;
	bCanTakeDown = false;

	NextAttackChance = false;
	GoNextAttack = false;

	AttackCount = 0;

	EquippedMeleeWeapon->HitBoxOff();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	IsDeath = false;
}

void AHunter::EquipWeapon(EWeapon Weapon)
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	UTexture2D* EquippedWeaponTexture = nullptr;
	bool IsLeftChange = false;

	FTransform SpawnTrans;
	SpawnTrans.SetLocation(GetActorLocation() + FVector::DownVector * 10000.f);

	AWeapon* SpawnWeapon = nullptr;
	AWeapon* SpawnWeaponSheath = nullptr;
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::KeepWorld,false);

	switch (Weapon)
	{
	case EWeapon::EW_LeftFist:
	{
		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->Destroy();
			EquippedRangedWeapon = nullptr;
		}

		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_LeftFist], SpawnTrans);

		EquippedRangedWeapon = Cast<ARangedWeapon>(SpawnWeapon);
		EquippedRangedWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("LeftHandSocket"));

		IsLeftChange = true;
	}
		break;
	case EWeapon::EW_RightFist:
	{
		if (EquippedWeaponSheath)
		{
			EquippedWeaponSheath->Destroy();
			EquippedWeaponSheath = nullptr;
		}

		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->SetActive(true);
		}

		if (EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->Destroy();
			EquippedMeleeWeapon = nullptr;
		}

		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_RightFist], SpawnTrans);

		EquippedMeleeWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		EquippedMeleeWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));

		CurWeaponState = ECharacterWeaponState::ECWS_OnehandedWeapon;
	}
		break;
	case EWeapon::EW_SawCleaver:
	{
		if (EquippedWeaponSheath)
		{
			EquippedWeaponSheath->Destroy();
			EquippedWeaponSheath = nullptr;
		}

		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->SetActive(true);
		}

		if (EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->Destroy();
			EquippedMeleeWeapon = nullptr;
		}

		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_SawCleaver], SpawnTrans);

		EquippedMeleeWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		EquippedMeleeWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));

		CurWeaponState = ECharacterWeaponState::ECWS_OnehandedWeapon;
		
		EquippedWeaponTexture = GameIns->TextureMap[TEXT("SawCleaver")];
	}
		break;
	case EWeapon::EW_SawCleaver_Deformed:
	{
		if (EquippedWeaponSheath)
		{
			EquippedWeaponSheath->Destroy();
			EquippedWeaponSheath = nullptr;
		}
		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->SetActive(true);
		}

		if (EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->Destroy();
			EquippedMeleeWeapon = nullptr;
		}
		
		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_SawCleaver_Deformed], SpawnTrans);

		EquippedMeleeWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		EquippedMeleeWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));

		CurWeaponState = ECharacterWeaponState::ECWS_OnehandedWeapon;
		EquippedWeaponTexture = GameIns->TextureMap[TEXT("SawCleaver")];
	}
		break;
	case EWeapon::EW_GreatSword:
	{
		if (EquippedWeaponSheath)
		{
			EquippedWeaponSheath->Destroy();
			EquippedWeaponSheath = nullptr;
		}
		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->SetActive(true);
		}

		if (EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->Destroy();
			EquippedMeleeWeapon = nullptr;
		}
		
		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_GreatSword], SpawnTrans);

		EquippedMeleeWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		EquippedMeleeWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));

		SpawnWeaponSheath = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_GreatSword_Sheath], SpawnTrans);
		SpawnWeaponSheath->AttachToComponent(GetMesh(), AttachRules, TEXT("GreatSwordSheathSocket"));

		EquippedWeaponSheath = SpawnWeaponSheath;

		CurWeaponState = ECharacterWeaponState::ECWS_OnehandedWeapon;

		EquippedWeaponTexture = GameIns->TextureMap[TEXT("GreatSword")];
	}
		break;
	case EWeapon::EW_GreatSword_Deformed:
	{
		if (EquippedWeaponSheath)
		{
			EquippedWeaponSheath->Destroy();
			EquippedWeaponSheath = nullptr;
		}

		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->SetActive(false);
		}

		if (EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->Destroy();
			EquippedMeleeWeapon = nullptr;
		}

		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_GreatSword_Deformed], SpawnTrans);
	
		EquippedMeleeWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		EquippedMeleeWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));

		CurWeaponState = ECharacterWeaponState::ECWS_TwohandedWeapon;
		EquippedWeaponTexture = GameIns->TextureMap[TEXT("GreatSword")];
	}
	break;
	case EWeapon::EW_Katana:
	{
		if (EquippedWeaponSheath)
		{
			EquippedWeaponSheath->Destroy();
			EquippedWeaponSheath = nullptr;
		}
		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->SetActive(true);
		}

		if (EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->Destroy();
			EquippedMeleeWeapon = nullptr;
		}

		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_Katana], SpawnTrans);

		EquippedMeleeWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		EquippedMeleeWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));
		
		SpawnWeaponSheath = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_Katana_Sheath], SpawnTrans);
		SpawnWeaponSheath->AttachToComponent(GetMesh(), AttachRules, TEXT("KatanaSheathSocket"));

		EquippedWeaponSheath = SpawnWeaponSheath;

		CurWeaponState = ECharacterWeaponState::ECWS_OnehandedWeapon;

		EquippedWeaponTexture = GameIns->TextureMap[TEXT("Katana")];
	}
	break;
	case EWeapon::EW_Katana_Deformed:
	{
		if (EquippedWeaponSheath)
		{
			EquippedWeaponSheath->Destroy();
			EquippedWeaponSheath = nullptr;
		}

		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->SetActive(false);
		}

		if (EquippedMeleeWeapon)
		{
			EquippedMeleeWeapon->Destroy();
			EquippedMeleeWeapon = nullptr;
		}

		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_Katana_Deformed], SpawnTrans);

		EquippedMeleeWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		EquippedMeleeWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));

		SpawnWeaponSheath = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_Katana_Sheath], SpawnTrans);
		SpawnWeaponSheath->AttachToComponent(GetMesh(), AttachRules, TEXT("KatanaSheathSocket"));

		CurWeaponState = ECharacterWeaponState::ECWS_TwohandedWeapon;
		EquippedWeaponTexture = GameIns->TextureMap[TEXT("Katana")];

	}
		break;
	case EWeapon::EW_HunterPistol:
	{
		if (EquippedRangedWeapon)
		{
			EquippedRangedWeapon->Destroy();
			EquippedRangedWeapon = nullptr;
		}

		SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponList[EWeapon::EW_HunterPistol], SpawnTrans);

		EquippedRangedWeapon = Cast<ARangedWeapon>(SpawnWeapon);
		EquippedRangedWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("LeftHandSocket"));

		EquippedWeaponTexture = GameIns->TextureMap[TEXT("HunterPistol")];
		IsLeftChange = true;
	}
		break;
	default:
		break;
	}

	if (EquippedRangedWeapon)
	{
		EquippedRangedWeapon->SetOwner(this);

	}

	if (EquippedMeleeWeapon)
	{
		EquippedMeleeWeapon->SetOwner(this);
	}


	if (IsLeftChange)
	{
		BBOverlay->SetRangedWeaponImage(EquippedWeaponTexture);
	}
	else
	{
		BBOverlay->SetMeleeWeaponImage(EquippedWeaponTexture);
	}

}

void AHunter::SwapWeapon(EWeaponType WeaponType, int32 ListNum)
{
	if (ListNum > MaxListNum) return;
	if (ListNum == MaxListNum) ListNum = 0;

	switch (WeaponType)
	{
	case EWeaponType::EWT_RangedWeapon:
		CurRangedListNum = ListNum;
		EquipWeapon(RangedWeaponsInPocket[CurRangedListNum]);
		break;
	case EWeaponType::EWT_MeleeWeapon:
		CurMeleeListNum = ListNum;
		EquipWeapon(MeleeWeaponsInPocket[CurMeleeListNum]);
		break;
	case EWeaponType::EWT_TwoHand:
		CurMeleeListNum = ListNum;
		EquipWeapon(MeleeWeaponsInPocket[CurMeleeListNum]);
		break;
	default:
		break;
	}

	
}

FString AHunter::GetWeaponStateToString(ECharacterWeaponState _WeaponState)
{
	FString WeaponStateName;
	switch (_WeaponState)
	{
	case ECharacterWeaponState::ECWS_Unoccupied:
		WeaponStateName = TEXT("None");
		break;
	case ECharacterWeaponState::ECWS_OnehandedWeapon:
		WeaponStateName = TEXT("OneHanded_");
		break;
	case ECharacterWeaponState::ECWS_TwohandedWeapon:
		WeaponStateName = TEXT("TwoHanded_");
		break;
	default:
		WeaponStateName = TEXT("None");
		break;
	}

	return WeaponStateName;

}

void AHunter::WeaponSlotUpdate()
{
	for (int i = 0; i < 3; i++)
	{

		if ((*RightHandSlotData[i]) == nullptr)
		{
			MeleeWeaponsInPocket[i] = EWeapon::EW_RightFist;
			continue;
		}

		EWeapon Weapon = (**RightHandSlotData[i]).Weapon;

		switch (Weapon)
		{
		case EWeapon::EW_SawCleaver:
			MeleeWeaponsInPocket[i] = EWeapon::EW_SawCleaver;
			break;
		case EWeapon::EW_GreatSword:
			MeleeWeaponsInPocket[i] = EWeapon::EW_GreatSword;
			break;
		case EWeapon::EW_Katana:
			MeleeWeaponsInPocket[i] = EWeapon::EW_Katana;
			break;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if ((*LeftHandSlotData[i]) == nullptr)
		{
			RangedWeaponsInPocket[i] = EWeapon::EW_LeftFist;
			continue;
		}

		EWeapon Weapon = (**LeftHandSlotData[i]).Weapon;

		switch (Weapon)
		{
		case EWeapon::EW_HunterPistol:
			RangedWeaponsInPocket[i] = EWeapon::EW_HunterPistol;
			break;
		case EWeapon::EW_GreatSword:
			RangedWeaponsInPocket[i] = EWeapon::EW_GreatSword;
			break;
		case EWeapon::EW_Katana:
			RangedWeaponsInPocket[i] = EWeapon::EW_Katana;
			break;
		default:
			RangedWeaponsInPocket[i] = EWeapon::EW_LeftFist;
		}
	}

	if (MeleeWeaponsInPocket[CurMeleeListNum] != EquippedMeleeWeapon->Weapon)
	{
		EquipWeapon(MeleeWeaponsInPocket[CurMeleeListNum]);
	}

	if (RangedWeaponsInPocket[CurRangedListNum] != EquippedRangedWeapon->Weapon)
	{
		EquipWeapon(RangedWeaponsInPocket[CurRangedListNum]);
	}

}

void AHunter::UseItemSlotUpdate()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());

	if(*UseItemSlotData[CurUseItemListNum] == nullptr)
	{
		BBOverlay->SetUseItemImage(nullptr);
		BBOverlay->ItemNum->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		EItem Item = (**UseItemSlotData[CurUseItemListNum]).Item;

		switch (Item)
		{
		case EItem::Potion:
			BBOverlay->SetUseItemImage(GameIns->TextureMap["Potion"]);
			break;
		case EItem::FireBottle:
			BBOverlay->SetUseItemImage(GameIns->TextureMap["FireBottle"]);
			break;
		case EItem::Stone:
			BBOverlay->SetUseItemImage(GameIns->TextureMap["Stone"]);
			break;
		}
		BBOverlay->ItemNum->SetText(FText::FromString(FString::FromInt((**UseItemSlotData[CurUseItemListNum]).Number)));
		BBOverlay->ItemNum->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHunter::UseItem()
{
	if ((*UseItemSlotData[CurUseItemListNum]) == nullptr) return;
	if ((**UseItemSlotData[CurUseItemListNum]).ItemType != EItemType::UseItem) return;

	GetInventory()->UseItem((**UseItemSlotData[CurUseItemListNum]).Index);

	UseItemSlotUpdate();
	PotionBulletUpdate();
}

void AHunter::PotionBulletUpdate()
{
	BBOverlay->PotionNum->SetText(FText::FromString(FString::FromInt(GetPotionNum())));
	BBOverlay->BulletNum->SetText(FText::FromString(FString::FromInt(GetBulletNum())));
}

void AHunter::DisplayGoldUpdate(float _DeltaTime)
{
	float Gap = static_cast<float>(abs(CurStatus.DisplayGold - CurStatus.Gold));

	if (FMath::IsNearlyZero(Gap)) return;

	if (CurStatus.DisplayGold > CurStatus.Gold)
	{
		CurStatus.DisplayGold = FMath::Clamp(CurStatus.DisplayGold - 200.f * _DeltaTime, CurStatus.Gold, INT_MAX);
	}
	else
	{
		CurStatus.DisplayGold = FMath::Clamp(CurStatus.DisplayGold + 200.f * _DeltaTime, 0, CurStatus.Gold);
	}
}

int AHunter::GetPotionNum()
{
	for (FInvenSlotData Data : GetInventory()->Inventory)
	{
		if (Data.Item == EItem::Potion)
		{
			return Data.Number;
		}
	}
	
	return 0;
}

int AHunter::GetBulletNum()
{
	for (FInvenSlotData Data : GetInventory()->Inventory)
	{
		if (Data.Item == EItem::Bullet)
		{
			return Data.Number;
		}
	}

	return 0;
}
void AHunter::Throw()
{
	if ((*UseItemSlotData[CurUseItemListNum]) == nullptr) return;
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && MontageMap[TEXT("Throw")])
	{
		CurActionState = ECharacterActionState::ECAS_Throw;
		AnimInstance->Montage_Play(MontageMap[TEXT("Throw")]);
	}
}

void AHunter::SpawnThrowObject()
{
	EItem Item = (**UseItemSlotData[CurUseItemListNum]).Item;

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(GetActorLocation() + GetActorForwardVector() * 100.f + GetActorUpVector() * 100.f);

	FRotator Rotation = GetActorRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	AThrowObject* Obj = nullptr;

	switch (Item)
	{
	case EItem::FireBottle:
	{
		Obj = GetWorld()->SpawnActor<AThrowObject>(GameIns->ThrowObjects[TEXT("FireBottle")], SpawnTrans);
		break;
	}
	case EItem::Stone:
		Obj = GetWorld()->SpawnActor<AThrowObject>(GameIns->ThrowObjects[TEXT("Stone")], SpawnTrans);
		break;
	default:
		break;
	}

	if (Obj != nullptr)
	{
		Obj->SetActorRotation(YawRotation);
		Obj->ProjectileMovementComponent->Velocity = GetActorForwardVector() * 400.f + GetActorUpVector() * 400.f;
		if (LockOnTarget)
		{
			Obj->ProjectileMovementComponent->HomingTargetComponent = LockOnTarget->GetRootComponent();
		}
		UseItem();
	}
}

void AHunter::Drink()
{
	if (CurActionState != ECharacterActionState::ECAS_Unoccupied) return;
	if (GetPotionNum() == 0) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && MontageMap[TEXT("Drink")])
	{
		CurActionState = ECharacterActionState::ECAS_Drink;
		AnimInstance->Montage_Play(MontageMap[TEXT("Drink")]);
	}
}

void AHunter::Heal()
{
	for (FInvenSlotData& Data : GetInventory()->Inventory)
	{
		if (Data.Item == EItem::Potion)
		{
			Data.Number--;
			GetAttribute()->Heal(HealAmount);
		}
	}

	PotionBulletUpdate();
}

int AHunter::GetCurDamage(int _Strength)
{
	if (_Strength == 0)
	{
		return EquippedMeleeWeapon->WeaponBaseDamage + EquippedMeleeWeapon->DamageScale * CurStatus.Strength;
	}

	return EquippedMeleeWeapon->WeaponBaseDamage + EquippedMeleeWeapon->DamageScale * _Strength;
}

void AHunter::StatusUpdate()
{
	GetAttribute()->MaxHp = BaseHp + VitalityScale * CurStatus.Vitality;
	GetAttribute()->MaxStamina = BaseStamina + EnduranceScale * CurStatus.Endurance;
	GetAttribute()->RegainAmount = GetAttribute()->MaxHp / 4.f;
}

void AHunter::StaminaUpdate(float DeltaTime)
{
	if (bExhaust)
	{
		AccExhaustTime -= DeltaTime;
		
		if (AccExhaustTime < 0.f)
		{
			bExhaust = false;
			AccExhaustTime = ExhaustTime;

			GetAttribute()->Stamina = 1.f;
		}
	}

	if (FMath::IsNearlyZero(GetAttribute()->Stamina) && !bExhaust)
	{
		bExhaust = true;
	}

	if (CurActionState == ECharacterActionState::ECAS_Unoccupied && !bExhaust && !bIsRun)
	{
		GetAttribute()->Stamina = FMath::Clamp(GetAttribute()->Stamina + GetAttribute()->StaminaRecoverSpeed * DeltaTime, 0.f, GetAttribute()->MaxStamina);
	}

	if (bIsRun)
	{
		GetAttribute()->Stamina = FMath::Clamp(GetAttribute()->Stamina - GetAttribute()->StaminaRecoverSpeed * 0.3f * DeltaTime, 0.f, GetAttribute()->MaxStamina);
		if (bExhaust)
		{
			GetCharacterMovement()->MaxWalkSpeed = 400.f;
			bIsRun = false;
		}
	}
}

void AHunter::ConsumeStamina()
{
	GetAttribute()->ConsumeStamina(ConsumeStaminaAmount);
}

