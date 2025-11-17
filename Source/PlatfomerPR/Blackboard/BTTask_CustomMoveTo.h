// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_CustomMoveTo.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API UBTTask_CustomMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_CustomMoveTo();

	UPROPERTY(EditAnywhere, Category = "Custom")
	float CustomAcceptableRadius = 100.0f;


protected:

	virtual EBTNodeResult::Type PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Custom")
	FBlackboardKeySelector RadiusKey;

};
