// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIMonsterController.generated.h"


class UBehaviorTree;
class AMonsterBase;
/**
 *
 */
UCLASS()
class PLATFOMERPR_API AAIMonsterController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;


protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;


private:


	//플레이어가 인지될때 핸들함수
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


private:

	AMonsterBase* Character;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr < UBehaviorTree> AIBehavior;


	AActor* Player;
};
