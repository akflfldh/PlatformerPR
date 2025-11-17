// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlatfomerPRCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCharacterAnimInstance;
class UCustomCharacterMovementComponent;
class ABaseButton;
class ARotatingObstacle;
class USphereComponent;
class AEquippableItem;
class UAIPerceptionStimuliSourceComponent;
class UHealthComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


enum class EAttackDir : uint8
{
	EFront = 0,
	ERight,
	EBack,
	ELeft
};



UCLASS(config = Game)
class APlatfomerPRCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlatfomerPRCharacter(const FObjectInitializer& ObjectInitializer);

#pragma region Component


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	USphereComponent* ItemOverlapTriggerComponent;


	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> AIPerceptionStimuliSourceComponent;

	UPROPERTY(VisibleAnywhere, Category = "Wall")
	TObjectPtr<UCapsuleComponent> WallJumpOverlapLeftComponent;

	UPROPERTY(VisibleAnywhere, Category = "Wall")
	TObjectPtr<UCapsuleComponent> WallJumpOverlapRightComponent;




	UPROPERTY(VisibleAnywhere, Category = "Wall")
	TObjectPtr<UCapsuleComponent> WallJumpOverlapComponent;





#pragma endregion 

#pragma region InputAction

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* FlyingMappingContext;



	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FlyMoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FlyBreakAction;




	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PressButtonAction;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EnterPortalAction;




#pragma endregion



	UCharacterAnimInstance* CharacterAnimInstance;


public:


	void AddButton(ABaseButton* button);
	void RemoveButton(ABaseButton* button);


	void AddMovementInputObstacle(ARotatingObstacle* obstacle);
	void RemoveMovementInputObstacle(ARotatingObstacle* obstacle);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
protected:

#pragma region InputAction
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void MoveFly(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void Attack(const FInputActionValue& Value);
	void Jump() override;

	void PressButton(const FInputActionValue& Value);


	void EnterPortal();


#pragma endregion

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	virtual void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



#pragma region Montage

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> KnockbackInAirMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> KnockbackLandMontage;


	void OnKnockbackLandMontageEnded(UAnimMontage* Montage, bool bInterrputed);

#pragma endregion

private:

	void ApplyMovementInputObstacle();




	void OnBeginOverlapEquippableItem(AEquippableItem* EquippableItem);



	void SetInputMappingContext(UInputMappingContext* InputMappingContext, int32 priority);
	void RemoveInputMappingContext(UInputMappingContext* InputMappingContext);

	//몬스터 머리를 밞았는가? 
	bool OnMonsterHeadStomped(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Landed(const FHitResult& Hit) override;

	bool TryWallJump();
	bool FindJumpWallNormal(FVector& oWallNormal);


	void PlayHitReact(AActor* DamageCauser, const FDamageEvent& DamageEvent);

#pragma region Overlap

	UFUNCTION()
	void OnBeginItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	UFUNCTION()
	void OnBeginInteractActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndInteractActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);






	//벽에 충돌 -> 벽점프 가능
	UFUNCTION()
	void OnWallLeftBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWallRightBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//벽에서 벗어남 
	UFUNCTION()
	void OnWallLeftEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnWallRightEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



	UFUNCTION()
	void OnWallBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnWallEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


#pragma endregion


	//캐릭터방향,거리를 고려해서 가장 적절한 오버랩된 Interact Actor를 가져온다.
	AActor* GetBestInteractOverlapActor() const;


	ABaseButton* GetNearButton();


	void CalculateAttackedDirection(const FVector& AttackerLocation);
	void PlayAttackedMontage();

private:


	UCustomCharacterMovementComponent* CustomMovementComponent;
	TArray<ABaseButton*> PressableButtonList;

	TArray<ARotatingObstacle*> MovementInputObstacleArray;



	bool bCanLeftWallJump = false;
	bool bCanRightWallJump = false;
	bool bCanWallJump = false;
	TObjectPtr<AActor> currWall;
	TObjectPtr<AActor> preWall;


	//-1 :left  1 :right 
	float ChachedLeftRightMoveInput = 0.0f;


	//오버랩된 상호작용가능한 액터 리스트
	TArray <TWeakObjectPtr<AActor>> InteractActorList;


	bool bKnockbackInAir = false;
	bool bInputLock = false;


	//플레이어 공격당한 방향
	EAttackDir AttackedDirection;

};

