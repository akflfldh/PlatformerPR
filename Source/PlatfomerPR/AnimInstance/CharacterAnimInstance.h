// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 *
 */
class APlatfomerPRCharacter;
class UCharacterMovementComponent;

UCLASS()
class PLATFOMERPR_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;



	void SetAttack(bool flag);

	bool GetShouldMoveFlag()const;

	bool IsFlying() const;

	void SetFlyingBreak(bool state);

	void SetJumpStart(bool flag);
	bool GetJumpStart() const;

	void SetJumping(bool flag);
	bool GetJumping() const;

	void SetDoubleJumping(bool flag);
	bool GetDoubleJumping() const;

	void Onlanded();

	bool GetInAirFlag() const;


	void PlayDoubleJumpMontage();




	void SetWallJumping(bool flag);
	bool GetWallJumping() const;


public:

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	//UAnimMontage* DoubleJumpMontage;


private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bShouldMove = false;
	void GetShouldMove();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	float GroundSpeed = 0.0f;
	void GetGroundSpeed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bAttack = false;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bFlyingMode = false;
	void GetFlying();



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bFlyingBreak = false;
	void GetFlyingBreak();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bJumping = false;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bDoubleJumping = false;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bJumpStart = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bInAir = false;
	void GetInAir();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bWallJumping = false;






	APlatfomerPRCharacter* PlatfomerPRCharacter;
	UCharacterMovementComponent* MovementComponent;





};
