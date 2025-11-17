// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableActor.h"
#include "FallablePlatformController.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API AFallablePlatformController : public AActivatableActor
{
	GENERATED_BODY()





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AFallablePlatformController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnActivate() override;



private:
	//플랫폼들을 모두제거
	void ResetPlatformList();


	//플랫폼들 생성
	void GeneratePlatformList();



private:

	//플랫폼리스트를 유지하고 
	//reset해서 기존리스트 플랫폼들제거 
	//다시생성
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetPosition;

	TArray<AActor*> PlatformList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlatformClass;
};
