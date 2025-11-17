// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSlimeMonster.h"

#include "GameFramework/CharacterMovementComponent.h"
#include"PlatfomerPR/AnimInstance/MonsterAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlatfomerPR/PlatfomerPRCharacter.h"
#include"Kismet/GameplayStatics.h"
#include "SlimeMonsterDataAsset.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"



ABossSlimeMonster::ABossSlimeMonster()
{
	bAttackAvailable = true;
}

void ABossSlimeMonster::Attack(AActor* actor)
{
	Super::Attack(actor);


	if (actor)
	{

		FVector PlayerLocation = actor->GetActorLocation();
		FVector MonsterLocation = GetActorLocation();

		FVector ToPlayerWorld = PlayerLocation - MonsterLocation;
		FVector ToPlayerDir = ToPlayerWorld.GetSafeNormal();

		float JumpStrength = 500;
		float fowardStrength = ToPlayerWorld.Length() + 30;
		ToPlayerDir *= fowardStrength;

		//ToPlayerDir.X *= fowardStrength;
		//ToPlayerDir.Y *= fowardStrength;
		ToPlayerDir.Z = JumpStrength;
		LaunchVelocity = ToPlayerDir;


		//해당 LaunchVelocity 로 날라갈떄 예상도착지점을 lineTrace로 게산하자 

		FPredictProjectilePathParams PredictProjectilePathParam(0.0f, MonsterLocation, LaunchVelocity, 10, ECC_Visibility, this);
		PredictProjectilePathParam.DrawDebugType = EDrawDebugTrace::ForDuration;
		PredictProjectilePathParam.DrawDebugTime = 3.0f;
		PredictProjectilePathParam.ActorsToIgnore.Add(actor);
		FPredictProjectilePathResult PredictProjectilePathResult;


		if (UGameplayStatics::PredictProjectilePath(this, PredictProjectilePathParam, PredictProjectilePathResult))
		{
			FVector PredictedLandingLocation = PredictProjectilePathResult.HitResult.ImpactPoint;
			SpawnAttackWaringDecal(PredictedLandingLocation);
		}


		if (MonstaerAnimInstance)
		{
			MonstaerAnimInstance->SetJumping(true);
		}
	}
	else
	{
		LaunchVelocity = { 0,0,0 };

	}

}

void ABossSlimeMonster::CancelAttack()
{
	Super::CancelAttack();
	if (MonstaerAnimInstance)
	{

		MonstaerAnimInstance->SetJumping(false);
		MonstaerAnimInstance->SetAttack(false);


	}


}

void ABossSlimeMonster::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{

	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (PrevMovementMode == EMovementMode::MOVE_Falling && MonstaerAnimInstance && MonstaerAnimInstance->GetAttack() && MonstaerAnimInstance->GetJumping())
	{

		//플레이어와 충돌했는지 판정
		TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypeQuertyArray;
		ObjectTypeQuertyArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

		TArray<AActor*> OutActorArray;


		const FVector SlimeLocation = GetActorLocation();

		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SlimeLocation, AttackRadius, ObjectTypeQuertyArray, APlatfomerPRCharacter::StaticClass(),
			{}, OutActorArray);


		//플레이어들과 충돌했다면 플레이어를 밀어버린다. 슬라임에서 몬스터 방향으로 


		for (auto actor : OutActorArray)
		{
			APlatfomerPRCharacter* Player = Cast<APlatfomerPRCharacter>(actor);

			if (Player)
			{
				FVector KnockbackDir = (Player->GetActorLocation() - SlimeLocation);
				KnockbackDir.Z = 0;
				KnockbackDir = KnockbackDir.GetSafeNormal();

				KnockbackDir *= KnockbackXYStrength;
				KnockbackDir.Z = KnockbackZStrength;

				Player->LaunchCharacter(KnockbackDir, true, true);
			}

		}

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

		//failing에서 에서 착지할떄
		MonstaerAnimInstance->SetJumping(false);

	}


	//생성한 데칼이있다면 제거
	if (AttackLandingSpawnedDecal)
	{
		AttackLandingSpawnedDecal->SetVisibility(false);
	}

}

void ABossSlimeMonster::OnStomped_Implementation(AActor* StompingActor)
{


	UE_LOG(LogTemp, Display, TEXT("Stomp_Imple"));

	Destroy();
}

void ABossSlimeMonster::AttackBeginNotify()
{
	Super::AttackBeginNotify();


	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	LaunchCharacter(LaunchVelocity, true, true);

}

void ABossSlimeMonster::SpawnAttackWaringDecal(const FVector& SpawnLocation)
{

	if (AttackLandingSpawnedDecal == nullptr)
	{
		USlimeMonsterDataAsset* SlimeDataAsset = Cast<USlimeMonsterDataAsset>(MonsterDataAsset);
		if (SlimeDataAsset && SlimeDataAsset->AttackLandingWarningDecalMaterial)
		{
			AttackLandingSpawnedDecal = NewObject<UDecalComponent>(this);
			AttackLandingSpawnedDecal->SetDecalMaterial(SlimeDataAsset->AttackLandingWarningDecalMaterial);
			AttackLandingSpawnedDecal->RegisterComponent();

			AttackLandingSpawnedDecal->DecalSize = { AttackRadius,AttackRadius,AttackRadius };

		}

	}

	AttackLandingSpawnedDecal->SetWorldLocation(SpawnLocation);

	AttackLandingSpawnedDecal->SetVisibility(true);

}
