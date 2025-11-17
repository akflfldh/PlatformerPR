// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StageSelectCameraPawn.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AStageActor;
class AStageSelectActor;
UCLASS()
class PLATFOMERPR_API AStageSelectCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStageSelectCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void LeftMoveStage();
	void RightMoveStage();
	void EnterStage();



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;


private:
	void SetSelectStageLocation();



private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UCameraComponent> CameraComponent;



#pragma region InputAction

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftArrowAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction>RightArrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction>EnterAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Stage")
	TArray<AStageActor*> StageActorList;

	UPROPERTY(EditAnywhere, Category = "Stage")

	TObjectPtr<AStageSelectActor> StageSelectActor;


	UPROPERTY(EditAnywhere, Category = "Stage")
	int CurrentStageIndex = 0;

};
