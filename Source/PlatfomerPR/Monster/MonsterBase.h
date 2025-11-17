// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

class UMonsterBaseDataAsset;
class UHealthComponent;
class UAIPerceptionComponent;
class UMonsterAnimInstance;
class UAISenseConfig_Sight;
UCLASS(Blueprintable, BlueprintType)
class PLATFOMERPR_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

	virtual void Attack(AActor* actor);
	virtual void CancelAttack();


	float GetBodyKnockbackXYStrength() const;
	float GetBodyKnockbackZStrength() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	TObjectPtr<UAIPerceptionComponent> GetAIPerceptionComponent() const;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	TObjectPtr<UMonsterBaseDataAsset> MonsterDataAsset;

	UMonsterAnimInstance* MonstaerAnimInstance;


#pragma region Component

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UHealthComponent> HealthComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;



	//플레이어와 접촉하면 플레이어는 공격당한것으로 판정된다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UCapsuleComponent> BodyComponent;


	//플레이어가 몬스터의 몸통과 충돌
	UFUNCTION()
	void OnBeginBodyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndBodyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);





#pragma endregion

	UAISenseConfig_Sight* AISenseConfig_Sight;


private:

protected:
#pragma region NotifyFunction

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	virtual void AttackBeginNotify();

#pragma endregion







private:


	//기본 동작 : actor 제거
	UFUNCTION()
	virtual void HandleDeath();



	//기본적으로 넉백에대한 정보를 가진다.
	UPROPERTY(EditAnywhere, Category = "Attack")
	float BodyKnockbackStrengthZ = 1500.0f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float BodyKnockbackStrengthXY = 1500.0f;



#pragma region Init

	void InitAIPerception();


#pragma endregion



};
