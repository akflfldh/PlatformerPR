// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"
#include"Kismet/GameplayStatics.h"

void UCustomCharacterMovementComponent::SetFlyingBreak(bool state)
{
	bFlyingBreak = state;

}

bool UCustomCharacterMovementComponent::GetFlyingBreak() const
{
	return bFlyingBreak;
}

bool UCustomCharacterMovementComponent::DoJump(bool bReplayingMoves)
{

	bool ret = Super::DoJump(bReplayingMoves);

	if (ret)
	{
		//play sound
		if (JumpSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
		}

	}


	return ret;
}
