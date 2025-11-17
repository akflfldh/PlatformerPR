// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include"PlatfomerPR/AnimInstance/MonsterAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlatfomerPR/PlatfomerPRCharacter.h"
#include"Kismet/GameplayStatics.h"
#include "SlimeMonsterDataAsset.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"

ASlimeMonster::ASlimeMonster()
{
	MoveToAcceptableRadius = 0.0f;
	bAttackAvailable = false;
}
