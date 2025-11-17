// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CustomMoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
UBTTask_CustomMoveTo::UBTTask_CustomMoveTo()
{

	NodeName = TEXT("CustomMoveTo");
}

EBTNodeResult::Type UBTTask_CustomMoveTo::PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	float FianlAcceptableRadius = CustomAcceptableRadius;


	UBlackboardComponent* BlackbaordCom = OwnerComp.GetBlackboardComponent();

	if (BlackbaordCom && RadiusKey.SelectedKeyType != nullptr && RadiusKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Float::StaticClass()))
	{
		FianlAcceptableRadius = BlackbaordCom->GetValueAsFloat(RadiusKey.SelectedKeyName);
	}
	AcceptableRadius = FianlAcceptableRadius;
	return Super::PerformMoveTask(OwnerComp, NodeMemory);

}
