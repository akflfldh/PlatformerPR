// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include"PlatfomerPR/Components/HealthComponent.h"
#include"PlatfomerPR/MonsterBaseDataAsset.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include"PlatfomerPR/AnimInstance/MonsterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include<Components/CapsuleComponent.h>
#include<PlatfomerPR/LogHelper.h>

#include<PlatfomerPR/PlatfomerPRCharacter.h>
#include<Kismet/GameplayStatics.h>

#include<PlatfomerPR/DamageType/DefaultDamageType.h>

// Sets default values
AMonsterBase::AMonsterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	//GetMesh()->SetVisibility(false); // 렌더링 끄기
		//GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 충돌 끄기

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthCom"));
	//	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));

		//StaticMeshComponent->SetupAttachment(RootComponent);
	BodyComponent = CreateDefaultSubobject<UCapsuleComponent>(FName("BodyCom"));
	if (BodyComponent)
		BodyComponent->SetupAttachment(RootComponent);
	InitAIPerception();

}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	MonstaerAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());



	if (HealthComponent && MonsterDataAsset)
	{
		HealthComponent->SetMaxHealth(MonsterDataAsset->MaxHealth);
		HealthComponent->OnHealthZero.AddDynamic(this, &AMonsterBase::HandleDeath);
	}

	if (MonsterDataAsset)
	{
		AISenseConfig_Sight->SightRadius = MonsterDataAsset->SightRadius;
		AISenseConfig_Sight->LoseSightRadius = MonsterDataAsset->LoseSightRadius;
		AISenseConfig_Sight->PeripheralVisionAngleDegrees = MonsterDataAsset->PeripheralVisionAngleDegrees;
	}

	if (BodyComponent)
	{
		BodyComponent->OnComponentBeginOverlap.AddDynamic(this, &AMonsterBase::OnBeginBodyOverlap);
	}
	AController* C = GetController();
	UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), C ? *C->GetName() : TEXT("NULL"));
	UE_LOG(LogTemp, Warning, TEXT("MovementMode: %d"), GetCharacterMovement()->MovementMode);
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AMonsterBase::Attack(AActor* actor)
{
	UE_LOG(LogTemp, Display, TEXT("MonsterAttack"));

	if (MonstaerAnimInstance)
	{
		MonstaerAnimInstance->SetAttack(true);
	}






}

void AMonsterBase::CancelAttack()
{

	if (MonstaerAnimInstance)
	{
		MonstaerAnimInstance->SetAttack(false);
	}







}

float AMonsterBase::GetBodyKnockbackXYStrength() const
{
	return BodyKnockbackStrengthXY;
}

float AMonsterBase::GetBodyKnockbackZStrength() const
{
	return BodyKnockbackStrengthZ;
}

float AMonsterBase::GetMoveToAcceptableRadius() const
{
	return MoveToAcceptableRadius;
}

bool AMonsterBase::GetAttackAvailableFlag() const
{
	return bAttackAvailable;
}

float AMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HealthComponent)
	{
		HealthComponent->TakeDamage(AppliedDamage);
	}


	return AppliedDamage;
}

TObjectPtr<UAIPerceptionComponent> AMonsterBase::GetAIPerceptionComponent() const
{
	return AIPerceptionComponent;
}

void AMonsterBase::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{

	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	if (PrevMovementMode == EMovementMode::MOVE_Falling)
	{
		//failing에서 에서 착지할떄
		if (MonstaerAnimInstance)
		{
			MonstaerAnimInstance->SetFalling(false);
		}

	}
	else if (MoveComp->MovementMode == EMovementMode::MOVE_Falling)
	{

		if (MonstaerAnimInstance)
		{
			MonstaerAnimInstance->SetFalling(true);
		}
	}



}



void AMonsterBase::OnBeginBodyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (APlatfomerPRCharacter* Player = Cast<APlatfomerPRCharacter>(OtherActor))
	{
		PrintLog("Monster Body hit");

		UGameplayStatics::ApplyDamage(Player, 1, nullptr, this, UDefaultDamageType::StaticClass());
	}
}

void AMonsterBase::OnEndBodyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AMonsterBase::AttackBeginNotify()
{





}

void AMonsterBase::HandleDeath()
{

	UE_LOG(LogTemp, Display, TEXT("MonsterDeath"));
	Destroy();

}

void AMonsterBase::InitAIPerception()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerceptionCom"));



	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("AISenseConfig_Sight"));



	if (AIPerceptionComponent && AISenseConfig_Sight)
	{
		AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
		AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
		AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
		AISenseConfig_Sight->SightRadius = 500.0f;
		AISenseConfig_Sight->LoseSightRadius = 3000.0f;
		AISenseConfig_Sight->PeripheralVisionAngleDegrees = 180.0;
		AISenseConfig_Sight->SetStartsEnabled(true);

		AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

		AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());

		//나중에 반드시 호출
		AIPerceptionComponent->RequestStimuliListenerUpdate();
	}

}

