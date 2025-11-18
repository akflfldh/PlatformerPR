// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatfomerPRCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include"AnimInstance/CharacterAnimInstance.h"
#include"Components/CustomCharacterMovementComponent.h"
#include"BaseButton.h"
#include"Obstacle/RotatingObstacle.h"
#include<Components/SphereComponent.h>
#include"Item/EquippableItem.h"
#include"Monster/MonsterBase.h"
#include"PlatfomerPR/Interface/Stompable.h"
#include"PlatfomerPR/CollisionChannel.h"
#include "Engine/EngineTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include"LogHelper.h"
#include"Interface/InteractInterface.h"
#include"Components/HealthComponent.h"
#include "Engine/DamageEvents.h"
#include"PlatfomerPR/DamageType/DefaultDamageType.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APlatfomerPRCharacter

APlatfomerPRCharacter::APlatfomerPRCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass < UCustomCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	CustomMovementComponent = Cast<UCustomCharacterMovementComponent>(GetMovementComponent());
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	GetCharacterMovement()->bEnablePhysicsInteraction = true;
	GetCharacterMovement()->PushForceFactor = 1.0f;
	//GetCharacterMovement()->PushForcePointZOffsetFactor = 0.5f;    // 중심점 오프셋
	//GetCharacterMovement()->bPushForceUsingZOffset = true;         // 캐릭터 상단에 힘 가함




	//아이템 오버랩 컴포넌트 생성
	ItemOverlapTriggerComponent = CreateDefaultSubobject<USphereComponent>(FName("ItemTriggerCom"));

	ItemOverlapTriggerComponent->SetupAttachment(RootComponent);


	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(FName("AIPerceptionStimuliSourceCom"));

	WallJumpOverlapLeftComponent = CreateDefaultSubobject<UCapsuleComponent>(FName("WallJumpOverlapLeftCom"));
	WallJumpOverlapRightComponent = CreateDefaultSubobject<UCapsuleComponent>(FName("WallJumpOverlapRightCom"));
	WallJumpOverlapComponent = CreateDefaultSubobject<UCapsuleComponent>(FName("WallJumpOverlapCom"));

	if (WallJumpOverlapComponent)
	{
		WallJumpOverlapComponent->SetupAttachment(RootComponent);
	}


	JumpMaxCount = 2;



	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthCom"));

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}


void APlatfomerPRCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	CharacterAnimInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	ItemOverlapTriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnBeginItemOverlap);






	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionStimuliSourceComponent->RegisterWithPerceptionSystem();


	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlatfomerPRCharacter::OnCapsuleHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnBeginInteractActorOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnEndInteractActorOverlap);



	if (WallJumpOverlapLeftComponent)
	{
		WallJumpOverlapLeftComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnWallLeftBeginOverlap);
		WallJumpOverlapLeftComponent->OnComponentEndOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnWallLeftEndOverlap);
	}
	if (WallJumpOverlapRightComponent)
	{
		WallJumpOverlapRightComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnWallRightBeginOverlap);
		WallJumpOverlapRightComponent->OnComponentEndOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnWallRightEndOverlap);
	}

	if (WallJumpOverlapComponent)
	{
		WallJumpOverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnWallBeginOverlap);
		WallJumpOverlapComponent->OnComponentEndOverlap.AddDynamic(this, &APlatfomerPRCharacter::OnWallEndOverlap);
	}

}

void APlatfomerPRCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ApplyMovementInputObstacle();


	if (CharacterAnimInstance->IsFlying())
	{

		if (CharacterAnimInstance->GetShouldMoveFlag())
		{

			bUseControllerRotationPitch = true;
		}
		else
		{

			bUseControllerRotationPitch = false;
		}

	}

}

void APlatfomerPRCharacter::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//hit 주체가 몬스터이다?

	//판정 : 머리에서 몬스터를 밞았는가? 
	if (OnMonsterHeadStomped(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit))
	{
		return;
	}


}





//////////////////////////////////////////////////////////////////////////
// Input

void APlatfomerPRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlatfomerPRCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlatfomerPRCharacter::Look);


		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlatfomerPRCharacter::Attack);

		EnhancedInputComponent->BindAction(PressButtonAction, ETriggerEvent::Started, this, &APlatfomerPRCharacter::PressButton);


		EnhancedInputComponent->BindAction(FlyMoveAction, ETriggerEvent::Triggered, this, &APlatfomerPRCharacter::MoveFly);

		EnhancedInputComponent->BindAction(EnterPortalAction, ETriggerEvent::Started, this, &APlatfomerPRCharacter::EnterPortal);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlatfomerPRCharacter::AddButton(ABaseButton* button)
{
	PressableButtonList.Push(button);
}

void APlatfomerPRCharacter::RemoveButton(ABaseButton* button)
{
	PressableButtonList.Remove(button);
}

void APlatfomerPRCharacter::AddMovementInputObstacle(ARotatingObstacle* obstacle)
{

	MovementInputObstacleArray.Add(obstacle);

}

void APlatfomerPRCharacter::RemoveMovementInputObstacle(ARotatingObstacle* obstacle)
{
	MovementInputObstacleArray.Remove(obstacle);

}

float APlatfomerPRCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//일반적으로 Damage는 1 , 즉 라이프감소 1  
	//보스일경우에는 2일수도 


	HealthComponent->TakeDamage(Damage);
	//play hit react 뒤로 쓰러지는 에니메이션 등은 HealthCom에 콜백으로 바인딩했다, 알아서 라이프가 0이면 처리
	PlayHitReact(DamageCauser, DamageEvent);


	return Damage;
}


void APlatfomerPRCharacter::Move(const FInputActionValue& Value)
{
	if (bInputLock)
		return;


	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	ChachedLeftRightMoveInput = MovementVector.X;

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);


	}
}


void APlatfomerPRCharacter::MoveFly(const FInputActionValue& Value)
{

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();


	//	UE_LOG(LogTemp, Display, TEXT("fly y : %f"), MovementVector.Y);


	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);


		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);





		// get right vector 
		//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 



		if (MovementVector.Y < 0.0F)
		{
			UE_LOG(LogTemp, Display, TEXT("S Input"));
			if (CharacterAnimInstance)
			{

				//AddMovementInput(ForwardDirection, MovementVector.Y);
				CustomMovementComponent->BrakingDecelerationFlying = 2000.0f;
				CharacterAnimInstance->SetFlyingBreak(true);

			}
			else
			{

				AddMovementInput(ForwardDirection, MovementVector.Y);
				CustomMovementComponent->BrakingDecelerationFlying = 100;
				CharacterAnimInstance->SetFlyingBreak(false);

			}


		}
		else
		{
			AddMovementInput(ForwardDirection, MovementVector.Y);
			CustomMovementComponent->BrakingDecelerationFlying = 100;
			CharacterAnimInstance->SetFlyingBreak(false);
		}

		//	AddMovementInput(RightDirection, MovementVector.X);
	}

}


void APlatfomerPRCharacter::Look(const FInputActionValue& Value)
{

	if (bInputLock)
		return;

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlatfomerPRCharacter::Attack(const FInputActionValue& Value)
{

	//value 체크

	//play attack montage 

	//등등
	CharacterAnimInstance->SetAttack(true);



}

void APlatfomerPRCharacter::Jump()
{

	//check input available 메서드로 묶을수도있다. 향후
	if (bInputLock)
		return;

	//TryWallJump 
	// true - > return ;

	if (TryWallJump())
	{
		return;
	}
	else
	{
		if (CharacterAnimInstance)
		{
			CharacterAnimInstance->SetWallJumping(false);
		}
	}


	if (CanJump() && JumpCurrentCount == 0)
	{
		if (CharacterAnimInstance)
		{
			CharacterAnimInstance->SetJumpStart(true);
		}
	}

	if (CanJump() && JumpCurrentCount == 1)
	{
		if (CharacterAnimInstance)
		{
			//2단점프
			CharacterAnimInstance->SetDoubleJumping(true);
		}
	}

	Super::Jump();


}


void APlatfomerPRCharacter::PressButton(const FInputActionValue& Value)
{
	ABaseButton* ClosestButton = GetNearButton();

	if (ClosestButton != nullptr)
	{

		ClosestButton->OnPress();
	}
}

void APlatfomerPRCharacter::EnterPortal()
{
	//overlap된 interact actor들중 가장가까운 actor에게 
	//해당 입력을 전달한다.
	//그 actor가 포탈이라면 아마 포탈이 작동할것

	AActor* actor = GetBestInteractOverlapActor();

	if (actor)
	{
		IInteractInterface::Execute_Interact(actor, this, EPlayerInputType::EEnterPortal);
	}


}

void APlatfomerPRCharacter::OnKnockbackLandMontageEnded(UAnimMontage* Montage, bool bInterrputed)
{
	PrintLog("asd");
	bInputLock = false;
}

void APlatfomerPRCharacter::ApplyMovementInputObstacle()
{

	//FVector TotalVelocity = FVector::ZeroVector;
	//for (auto obstacle : MovementInputObstacleArray)
	//{
	//	FRotator Rotation = obstacle->GetRotationAxis() * (PI / 180.0f);


	//	FVector Pivot = obstacle->GetActorLocation();

	//	FVector CharacterLocation = GetActorLocation();

	//	FVector ToCharacterVector = CharacterLocation - Pivot;

	//	FVector TangentVector = FVector::CrossProduct(Rotation.Vector(), ToCharacterVector);

	//	TotalVelocity += TangentVector;


	//}
	//float FinaleVelocityScale = (TotalVelocity.Size() / GetMovementComponent()->GetMaxSpeed());

	//FVector FinalVelocity = TotalVelocity.GetSafeNormal();


	//FString str = FinalVelocity.ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("Final Velocity : %s"), *str);
	//AddMovementInput(FinalVelocity, FinaleVelocityScale);

	FVector TotalVelocity = FVector::ZeroVector;

	// 이 루프가 문제의 핵심입니다.
	for (auto obstacle : MovementInputObstacleArray)
	{
		// 1. (가정) obstacle에 FVector AngularVelocityDegrees 변수가 있다고 가정합니다.
		//    이 함수는 직접 만드셔야 합니다. (예: (0, 0, 90) - 초당 90도)
		FVector AngularVelocityDeg = obstacle->GetRotationAxis();


		// 2. 각속도를 라디안으로 변환합니다. (물리 공식은 라디안 사용)
		FVector AngularVelocityRad = AngularVelocityDeg * (PI / 180.f);

		// 3. 반지름 벡터 (r)
		FVector Pivot = obstacle->GetActorLocation();
		FVector ToCharacterVector = GetActorLocation() - Pivot;

		// 4. 접선 속도 (v = w x r)
		//    이제 AngularVelocityRad에 '속력' 정보가 포함되어 있으므로
		//    TangentVelocity는 (cm/s) 단위의 올바른 속도 벡터가 됩니다.
		FVector TangentVelocity = FVector::CrossProduct(AngularVelocityRad, ToCharacterVector);

		TotalVelocity += TangentVelocity;
	}

	// 5. 최대 속도 가져오기 (0으로 나눠지는 것 방지)
	float MaxSpeed = GetMovementComponent()->GetMaxSpeed();
	if (MaxSpeed <= 0.f) MaxSpeed = 1.f; // 안전장치

	// 6. 최종 스케일과 방향 계산
	float FinalScale = TotalVelocity.Size() / MaxSpeed;
	FVector FinalDirection = TotalVelocity.GetSafeNormal();

	// 로그 확인: FinalScale 값이 (예: 0.5, 1.0, 1.5)처럼 의미 있게 나오는지 확인

	FinalScale = FMath::Clamp(FinalScale, 0.0F, 1.5F);

	// 7. 올바른 함수 호출
	AddMovementInput(FinalDirection, FinalScale);
}

void APlatfomerPRCharacter::OnBeginItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{









	//Item 상위에서도 분류 type 제공하자
	AEquippableItem* EquippableItem = Cast<AEquippableItem>(OtherActor);
	if (EquippableItem)
	{
		OnBeginOverlapEquippableItem(EquippableItem);
	}








}

void APlatfomerPRCharacter::OnBeginInteractActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		PrintLog("Enter");
		InteractActorList.Add(OtherActor);
	}

}

void APlatfomerPRCharacter::OnEndInteractActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		InteractActorList.Remove(OtherActor);
	}

}

void APlatfomerPRCharacter::OnBeginOverlapEquippableItem(AEquippableItem* EquippableItem)
{


	const UStaticMeshComponent* StaticMeshCom = EquippableItem->GetStaticMeshComponent();
	for (auto& socketName : EquippableItem->GetSocketNameList())
	{


		UStaticMesh* MeshAsset = StaticMeshCom->GetStaticMesh();
		UStaticMeshComponent* ItemMeshCom = NewObject<UStaticMeshComponent>(this);
		ItemMeshCom->SetStaticMesh(MeshAsset);
		ItemMeshCom->SetSimulatePhysics(false);
		ItemMeshCom->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ItemMeshCom->RegisterComponent();


		ItemMeshCom->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);


	}
	//player를 wing fly movement 모드로 설정하자
	CustomMovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);

	UE_LOG(LogTemp, Display, TEXT("SSS"));

	RemoveInputMappingContext(DefaultMappingContext);
	SetInputMappingContext(FlyingMappingContext, 1);
	bUseControllerRotationPitch = true;



	EquippableItem->Destroy();


}

void APlatfomerPRCharacter::SetInputMappingContext(UInputMappingContext* InputMappingContext, int32 priority)
{
	if (InputMappingContext == nullptr) return;



	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{

			Subsystem->AddMappingContext(InputMappingContext, priority);
		}


	}




}


void APlatfomerPRCharacter::RemoveInputMappingContext(UInputMappingContext* InputMappingContext)
{
	if (InputMappingContext == nullptr) return;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);

		}
	}

}

bool APlatfomerPRCharacter::OnMonsterHeadStomped(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	//몬스터인가?
	AMonsterBase* Monster = Cast<AMonsterBase>(OtherActor);
	if (Monster == nullptr)
	{
		return false;
	}

	//플레이어의 위치가 더 높은가? 
	// 즉 몬스터의 머리보다 더 높은 위치에있는가?

	const FVector PlayerLocation = GetActorLocation();
	const FVector PlyaerVelocity = GetVelocity();

	const FVector MonsterLocation = Monster->GetActorLocation();

	const FVector MonsterUpVector = Monster->GetActorUpVector();
	const FVector ToPlayerFromMonsterDir = (PlayerLocation - MonsterLocation).GetSafeNormal();



	bool bAbove = FVector::DotProduct(MonsterUpVector, ToPlayerFromMonsterDir) > 0.8;
	if (bAbove)
	{
		UE_LOG(LogTemp, Display, TEXT("Stomping_Above True"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Stomping_Above False"));

	}


	bool bFalling = PlyaerVelocity.Z < 0.0F;

	//	const FVector MonsterHeadLocation = MonsterLocation + Monster->GetActorUpVector() * 30;
	UE_LOG(LogTemp, Display, TEXT("Stomping Check"));

	if (bAbove)
	{
		UE_LOG(LogTemp, Display, TEXT("Stomping Can"));

		//Monster
		if (Monster->Implements< UStompable>())
		{
			IStompable::Execute_OnStomped(Monster, this);
		}
		FVector NewVel = GetVelocity();
		NewVel.Z = 1000;
		LaunchCharacter(NewVel, true, true);


		return true;
	}
	else
	{

		return false;
	}



}

void APlatfomerPRCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);


	if (bKnockbackInAir)
	{

		if (KnockbackLandMontage)
		{
			if (CharacterAnimInstance)
			{




				PlayKnockbackLandMontage();
				FOnMontageEnded EndDelegate;
				EndDelegate.BindUObject(this, &APlatfomerPRCharacter::OnKnockbackLandMontageEnded);

				CharacterAnimInstance->Montage_SetEndDelegate(EndDelegate, KnockbackLandMontage);











			}
		}
		bKnockbackInAir = false;
	}

	if (CharacterAnimInstance)
	{
		CharacterAnimInstance->Onlanded();
	}

	preWall = nullptr;
	currWall = nullptr;

}
bool APlatfomerPRCharacter::TryWallJump()
{


	if (bCanWallJump == false || ((currWall != nullptr) && (preWall == currWall)))
	{
		if (bCanWallJump == false)
		{

			//UE_LOG(LogTemp, Display, TEXT("WallJump Can false"));

			PrintLog("WallJump Available ; False");

		}
		else if (currWall == currWall)
		{
			//	UE_LOG(LogTemp, Display, TEXT("WallJump wall same"));
			PrintLog("WallJump Wall Same");
		}

		return false;
	}

	//벽의 노멀을 구한다.
	FVector WallNormal;
	if (FindJumpWallNormal(WallNormal) == false)
	{
		return false;
	}
	UE_LOG(LogTemp, Display, TEXT("WallJump wall WallNormal"));
	//벽의 노멀방향의 반대방향으로 입력이 들어왔는지 확인




	//벽의 반대방향으로 캐릭터가 점프된다.


	const FVector UpVector = { 0,0,1 };

	FVector JumpDir = -WallNormal + UpVector;
	JumpDir = JumpDir.GetSafeNormal();



	const float Strength = 2000.0f;

	LaunchCharacter(JumpDir * Strength, true, true);

	CharacterAnimInstance->SetWallJumping(true);

	preWall = currWall;
	return true;
}

bool APlatfomerPRCharacter::FindJumpWallNormal(FVector& oWallNormal)
{
	//4방향 (앞,뒤,우,왼) 으로 레이를 쏴서 가장가까운 벽의 노멀을 구한다.

	const FVector PlayerLocation = GetActorLocation();

	float RayDist = 300.0f;


	const FVector CandidatesDir[4] = {

		GetActorForwardVector(),
		-GetActorForwardVector(),
		GetActorRightVector(),
		-GetActorRightVector()
	};

	float RayDistOver = RayDist + 1;
	FHitResult HitResult;
	HitResult.Distance = RayDistOver;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(ECC_WallTrace), false, this); //찾아볼것

	for (int i = 0; i < 4; ++i)
	{
		FHitResult HitResultTemp;
		const FVector RayStart = PlayerLocation - CandidatesDir[i] * 30;
		const FVector RayEnd = CandidatesDir[i] * RayDist + RayStart;
		DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Red, true);

		if (GetWorld()->LineTraceSingleByChannel(HitResultTemp, RayStart, RayEnd, ECC_WallTrace, Params))
		{
			UE_LOG(LogTemp, Display, TEXT("Wall aa"));
			if (HitResult.Distance > HitResultTemp.Distance)
			{
				HitResult = HitResultTemp;
			}
		}

	}

	if (HitResult.Distance == RayDistOver)
	{
		return false;
	}
	oWallNormal = HitResult.ImpactNormal;


	return true;
}

void APlatfomerPRCharacter::PlayHitReact(AActor* DamageCauser, const FDamageEvent& DamageEvent)
{

	if (AMonsterBase* monster = Cast<AMonsterBase>(DamageCauser))
	{


		float KnockbackStrengthXY = 0.0f;
		float KnockbackStrengthZ = 0.0f;

		const UDamageType* DamageType = DamageEvent.DamageTypeClass.GetDefaultObject();
		if (const UDefaultDamageType* DefaultDamageType = Cast <const UDefaultDamageType>(DamageType))
		{
			KnockbackStrengthXY = monster->GetBodyKnockbackXYStrength();
			KnockbackStrengthZ = monster->GetBodyKnockbackZStrength();
		}


		FVector ToMonsterDir = (monster->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();

		//FRotator ToMonsterRotator = ToMonsterDir.Rotation();
		//SetActorRotation(ToMonsterRotator);


		FVector KnockbackVelocity = -ToMonsterDir;
		KnockbackVelocity *= KnockbackStrengthXY;
		KnockbackVelocity.Z = KnockbackStrengthZ;
		LaunchCharacter(KnockbackVelocity, true, true);


		//플레이어 기준 몬스터가 공격한 방향 확인 
		CalculateAttackedDirection(monster->GetActorLocation());

		//해당방향에 맞는 knockback에니메이션몽타주 재생
		PlayKnockbackInAirMontage();






		bKnockbackInAir = true;
		bInputLock = true;
	}



}


void APlatfomerPRCharacter::OnWallLeftBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		bCanLeftWallJump = true;
	}
}

void APlatfomerPRCharacter::OnWallRightBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		bCanRightWallJump = true;
	}
}

void APlatfomerPRCharacter::OnWallLeftEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		bCanLeftWallJump = false;
	}
}

void APlatfomerPRCharacter::OnWallRightEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		bCanRightWallJump = false;
	}
}

void APlatfomerPRCharacter::OnWallBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Display, TEXT("WallOverlapBegin2"));

//	if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
//	{
	UE_LOG(LogTemp, Display, TEXT("WallOverlapBegin"));

	bCanWallJump = true;
	currWall = OtherActor;
	//}

}

void APlatfomerPRCharacter::OnWallEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	//if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
//	{
	UE_LOG(LogTemp, Display, TEXT("WallOverlapEnd"));

	bCanWallJump = false;
	currWall = nullptr;
	preWall = nullptr;
	//}

}

AActor* APlatfomerPRCharacter::GetBestInteractOverlapActor() const
{

	//캐릭터방향은 Forward를 기준으로 [-90  90]  

	//그중 거리가 가장가까운 actor를 선택한다.

	AActor* BestActor = nullptr;
	float MinDistance = FLT_MAX;
	const FVector ForwardVector = GetActorForwardVector();
	const FVector PlayerLocation = GetActorLocation();

	PrintLog("Best");
	for (auto actorWeakPtr : InteractActorList)
	{
		if (AActor* actor = actorWeakPtr.Get())
		{
			const FVector ActorLocation = actor->GetActorLocation();

			float dst = FVector::Dist(ActorLocation, PlayerLocation);

			if (FVector::DotProduct(ForwardVector, (ActorLocation - PlayerLocation).GetSafeNormal()) < 0)
			{
				continue;
			}

			if (dst < MinDistance)
			{
				MinDistance = dst;
				BestActor = actor;
			}

		}
	}



	return BestActor;
}




ABaseButton* APlatfomerPRCharacter::GetNearButton()
{
	ABaseButton* ClosestButton = nullptr;

	float MinDistance = FLT_MAX;


	FVector CharacterLocation = GetActorLocation();
	for (auto Button : PressableButtonList)
	{

		//가장 가까이있는버튼 하나를 찾아
		//그버튼을 누른다.

		if (Button == nullptr) continue;
		float Distance = FVector::Dist(Button->GetActorLocation(), CharacterLocation);
		//FVector::Dist()

		if (MinDistance > Distance)
		{
			ClosestButton = Button;
			MinDistance = Distance;
		}
	}


	return ClosestButton;

}

void APlatfomerPRCharacter::PlayKnockbackInAirMontage()
{
	//Play Animation
	if (KnockbackInAirMontage && CharacterAnimInstance)
	{
		FName SectionName = NAME_None;

		switch (AttackedDirection)
		{

		case EAttackDir::EFront:
			PrintLog("Front");
			SectionName = FName("Knockback_Front");
			break;
		case EAttackDir::EBack:
			PrintLog("Back");
			SectionName = FName("Knockback_Back");
			break;

		case EAttackDir::ERight:

			break;

		case EAttackDir::ELeft:

			break;
		}

		CharacterAnimInstance->Montage_Play(KnockbackInAirMontage);
		if (SectionName != NAME_None)
		{
			CharacterAnimInstance->Montage_JumpToSection(SectionName, KnockbackInAirMontage);
		}
	}

}

void APlatfomerPRCharacter::PlayKnockbackLandMontage()
{

	//Play Animation
	if (KnockbackLandMontage && CharacterAnimInstance)
	{
		FName SectionName = NAME_None;

		switch (AttackedDirection)
		{

		case EAttackDir::EFront:
			PrintLog("Front");
			SectionName = FName("Knockback_Front");
			break;
		case EAttackDir::EBack:
			PrintLog("Back");
			SectionName = FName("Knockback_Back");
			break;

		case EAttackDir::ERight:

			break;

		case EAttackDir::ELeft:

			break;
		}
		PrintLog("Land1");

		CharacterAnimInstance->Montage_Play(KnockbackLandMontage);
		if (SectionName != NAME_None)
		{
			PrintLog("Land");
			CharacterAnimInstance->Montage_JumpToSection(SectionName, KnockbackLandMontage);
		}
	}
}

void APlatfomerPRCharacter::CalculateAttackedDirection(const FVector& AttackerLocation)
{

	//  몬스터 쪽 방향 (월드 공간)
	FVector WorldDir = (AttackerLocation - GetActorLocation());
	WorldDir.Z = 0.f;
	WorldDir.Normalize();

	// 메쉬 기준 로컬 방향으로 변환
	FVector LocalDir = GetTransform().InverseTransformVectorNoScale(WorldDir);
	LocalDir.Z = 0.f;
	LocalDir.Normalize();

	// 이제 LocalDir.x / y 로 앞/뒤/좌/우 판정
	float ForwardAmount = LocalDir.X; // +면 앞, -면 뒤
	float RightAmount = LocalDir.Y; // +면 오른쪽, -면 왼쪽

	//PrintLog(ToAttackerDirLocal.ToCompactString());
	if (ForwardAmount >= 0.5f)
	{
		PrintLog("Front");
		AttackedDirection = EAttackDir::EFront;
	}
	else if (ForwardAmount <= -0.5f)
	{
		PrintLog("Back");
		AttackedDirection = EAttackDir::EBack;
	}
	else if (RightAmount > 0.5f)
	{
		AttackedDirection = EAttackDir::ERight;
	}
	else
	{
		AttackedDirection = EAttackDir::ELeft;
	}

	//ActorTransform의 방향 확인 
	FTransform T = GetActorTransform();

	DrawDebugLine(GetWorld(), T.GetLocation(), T.GetLocation() + T.GetUnitAxis(EAxis::X) * 120, FColor::Red, false, 2, 0, 4);  // Forward
	DrawDebugLine(GetWorld(), T.GetLocation(), T.GetLocation() + T.GetUnitAxis(EAxis::Y) * 120, FColor::Green, false, 2, 0, 4); // Right
	DrawDebugLine(GetWorld(), T.GetLocation(), T.GetLocation() + T.GetUnitAxis(EAxis::Z) * 120, FColor::Blue, false, 2, 0, 4);  // Up

}

