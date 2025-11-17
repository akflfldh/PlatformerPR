// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"


class USoundBase;

/**
 *
 */
UCLASS()
class PLATFOMERPR_API UCustomCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()


public:


	void SetFlyingBreak(bool state);
	bool GetFlyingBreak() const;


#pragma region OverridenFunction




protected:

	virtual bool DoJump(bool bReplayingMoves) override;




#pragma endregion


private:

	UPROPERTY(EditAnywhere)
	USoundBase* JumpSound;

	bool bFlyingBreak = false;

};
