// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

//FName NotifyName;
DECLARE_DELEGATE_OneParam(FOnMontageBeginNotify, FName)
/**
 *
 */
UCLASS()
class PLATFOMERPR_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void SetAttack(bool flag);
	void SetFalling(bool flag);
	void SetJumping(bool flag);

	bool GetAttack() const;
	bool GetJumping() const;
protected:




private:





private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bAttack = false;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bFalling = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool bJumping = false;



};
