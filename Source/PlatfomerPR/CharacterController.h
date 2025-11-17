// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API ACharacterController : public APlayerController
{
	GENERATED_BODY()



public:

	void RequsetStartStageSetting();
	void RequestStageSetting();


protected:
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintPure)
	int GetCrystalCount();

	UFUNCTION(BlueprintPure)
	int GetCoinCount();


	UFUNCTION(BlueprintPure)
	int GetEnergyCount();



private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDWidgetClass;


	UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartStageWidgetClass;

	UUserWidget* StartStageWidget;




};
