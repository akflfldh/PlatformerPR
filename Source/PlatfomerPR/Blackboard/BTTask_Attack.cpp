// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include"PlatfomerPR/Controller/AIMonsterController.h"
#include"PlatfomerPR/Monster/MonsterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");

}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//controller - pawn - monster -  attack

	AAIMonsterController* controller = Cast< AAIMonsterController>(OwnerComp.GetAIOwner());

	if (controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMonsterBase* Monster = Cast< AMonsterBase>(controller->GetPawn());

	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}

	AActor* player = Cast<AActor>(controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	Monster->Attack(player);


	return EBTNodeResult::Succeeded;
}
