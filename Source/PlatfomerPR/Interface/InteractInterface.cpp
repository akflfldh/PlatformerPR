// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractInterface.h"

// Add default functionality here for any IInteractInterface functions that are not pure virtual.
void IInteractInterface::Execute_Interact(AActor* InteraceActor, APlatfomerPRCharacter* player, EPlayerInputType inputType)
{
	if (IInteractInterface* Interface = Cast< IInteractInterface>(InteraceActor))
	{
		Interface->Interact(player, inputType);
	}
}
