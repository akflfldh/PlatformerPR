// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonsterController.h"
#include<Kismet/GameplayStatics.h>
#include"PlatfomerPR/Monster/MonsterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include"PlatfomerPR/LogHelper.h"
void AAIMonsterController::BeginPlay()
{

	Super::BeginPlay();

	if (AIBehavior)
	{

		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsFloat("MonsterAcceptableRadius", Character->GetMoveToAcceptableRadius());

		GetBlackboardComponent()->SetValueAsBool("bAttackAvailable", Character->GetAttackAvailableFlag());

	}
}

void AAIMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Character = Cast<AMonsterBase>(GetPawn());



	if (Character)
	{
		//AIPerceptionComponent를 가져와 플레이어를 인지했을때의 핸들 콜백등록		
		TObjectPtr<UAIPerceptionComponent> AIPerceptionCom =
			Character->GetAIPerceptionComponent();

		if (AIPerceptionCom)
		{
			AIPerceptionCom->OnTargetPerceptionUpdated.AddDynamic(this, &AAIMonsterController::OnTargetPerceptionUpdated);
		}



	}

}



void AAIMonsterController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

	//UE_LOG(LogTemp, Log, TEXT("AI perceived: %s"), *Actor->GetName());

	if (Stimulus.WasSuccessfullySensed())
	{
		PrintLog("Player Can see");
		SetFocus(Actor);
		Player = Actor;
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsObject(TEXT("Player"), Actor);
		}
	}
	else
	{
		PrintLog("Player Can't see");

		//더이상 시야에 보이지않는다.
		ClearFocus(EAIFocusPriority::Gameplay);
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		if (BlackboardComponent)
		{
			BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
			BlackboardComponent->ClearValue(TEXT("Player"));
		}

		if (Character)
		{
			Character->CancelAttack();
		}


		Player = nullptr;
	}
}
void AAIMonsterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Player)
	{
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

		if (BlackboardComponent)
		{
			PrintLog(Player->GetActorLocation().ToCompactString());
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), Player->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnwonPlayerLocation"), Player->GetActorLocation());
		}
	}
}
