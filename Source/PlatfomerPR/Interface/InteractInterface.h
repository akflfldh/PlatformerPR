// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include"PlatfomerPR/PlayerInputType.h"
#include"InteractInterface.generated.h"


class APlatfomerPRCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class PLATFOMERPR_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Interact(APlatfomerPRCharacter* player, EPlayerInputType inputType) = 0;

	static void Execute_Interact(AActor* InteraceActor, APlatfomerPRCharacter* player, EPlayerInputType inputType);
};
