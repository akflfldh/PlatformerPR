// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();


}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeUpdateAnimation(DeltaSeconds);



}

void UMonsterAnimInstance::SetAttack(bool flag)
{

	bAttack = flag;
	UE_LOG(LogTemp, Display, TEXT("Attack Anim"));

}

void UMonsterAnimInstance::SetFalling(bool flag)
{
	bFalling = flag;
	UE_LOG(LogTemp, Display, TEXT("Falling Anim"));
}

void UMonsterAnimInstance::SetJumping(bool flag)
{
	bJumping = flag;
}


bool UMonsterAnimInstance::GetAttack() const
{
	return bAttack;
}

bool UMonsterAnimInstance::GetJumping() const
{
	return bJumping;
}
