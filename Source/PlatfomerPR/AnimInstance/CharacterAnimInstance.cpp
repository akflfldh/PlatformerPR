// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include"PlatfomerPR/PlatfomerPRCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();


	PlatfomerPRCharacter = Cast<APlatfomerPRCharacter>(TryGetPawnOwner());

	if (PlatfomerPRCharacter)
	{
		MovementComponent = PlatfomerPRCharacter->GetCharacterMovement();
	}

}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//ABP에서 사용할 데이터를 수집하는 작업 수행
	//ex) GetShouldMove(); -> MovementComponent에서 속도를 보고 상태 처리

	GetGroundSpeed();
	GetShouldMove();
	GetFlying();
	GetFlyingBreak();
	GetInAir();


}

void UCharacterAnimInstance::SetAttack(bool flag)
{
	if (flag)
	{
		//PlayMontage(Attack);
		bAttack = true;
	}
	else
	{
		///몽타주 이른종료?
		bAttack = false;

	}

}

bool UCharacterAnimInstance::GetShouldMoveFlag() const
{
	return bShouldMove;
}

bool UCharacterAnimInstance::IsFlying() const
{
	return bFlyingMode;
}

void UCharacterAnimInstance::SetFlyingBreak(bool state)
{
	bFlyingBreak = state;
}

void UCharacterAnimInstance::SetJumpStart(bool flag)
{
	bJumpStart = flag;
}

bool UCharacterAnimInstance::GetJumpStart() const
{
	return bJumpStart;
}

void UCharacterAnimInstance::GetShouldMove()
{

	//movementComponent로부터 속도를 얻어와서 일정값 이상이면 true  그렇지않으면 false 로 설정한다.

	if (MovementComponent)
	{

		FVector CurrentAcceleration = MovementComponent->GetCurrentAcceleration();

		if (CurrentAcceleration.Size() > 0 && GroundSpeed > 5.0f)
		{
			bShouldMove = true;
		}
		else
		{
			bShouldMove = false;
		}
	}



}

void UCharacterAnimInstance::SetJumping(bool flag)
{
	bJumping = flag;

}
bool UCharacterAnimInstance::GetJumping() const
{
	return bJumping;

}

void UCharacterAnimInstance::SetDoubleJumping(bool flag)
{
	bDoubleJumping = flag;
}


bool UCharacterAnimInstance::GetDoubleJumping() const
{
	return bDoubleJumping;
}

void UCharacterAnimInstance::Onlanded()
{
	bJumping = false;
	bJumpStart = false;
	bDoubleJumping = false;
	SetWallJumping(false);
}

bool UCharacterAnimInstance::GetInAirFlag() const
{
	return bInAir;
}

void UCharacterAnimInstance::PlayDoubleJumpMontage()
{
	/*if (DoubleJumpMontage)
	{
		Montage_Play(DoubleJumpMontage);
	}*/
}


void UCharacterAnimInstance::SetWallJumping(bool flag)
{
	bWallJumping = flag;
}

bool UCharacterAnimInstance::GetWallJumping() const
{
	return bWallJumping;
}



void UCharacterAnimInstance::GetGroundSpeed()
{

	if (MovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(PlatfomerPRCharacter->GetVelocity());
	}


}

void UCharacterAnimInstance::GetFlying()
{

	if (MovementComponent)
	{

		if (MovementComponent->MovementMode == EMovementMode::MOVE_Flying)
		{
			bFlyingMode = true;
		}
		else
		{
			bFlyingMode = false;
		}

	}


}


void UCharacterAnimInstance::GetFlyingBreak()
{

	//if (IsFlying())
	//{


	//	FVector CurrentAcceleration = MovementComponent->GetCurrentAcceleration();

	//	if (CurrentAcceleration.Y < 0.0f)
	//	{
	//		bFlyingBreak = true;
	//		UE_LOG(LogTemp, Display, TEXT("FlyingBreak"));
	//	}
	//	else
	//	{
	//		bFlyingBreak = false;
	//	}


	//}
	//else
	//{
	//	bFlyingBreak = false;

	//}

}

void UCharacterAnimInstance::GetInAir()
{

	if (MovementComponent)
	{
		bInAir = MovementComponent->IsFalling();
	}

}
