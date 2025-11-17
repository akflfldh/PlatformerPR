// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseButton.generated.h"

class UBoxComponent;
class AActivatableActor;

//기본 버튼 , 누르면 설정된 TriggerActor의 OnTrigger호출 //바로바로 계속 누를수있음 


UCLASS(Abstract)
class PLATFOMERPR_API ABaseButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseButton();


	virtual void OnPress();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




	UPROPERTY(EditanyWhere)
	UBoxComponent* DetactComponent;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	//버튼을 누를수있는 범위에 들어왔다.
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//범위에서 벗어남
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma region Variable

	bool bInRange;


	UPROPERTY(EditAnywhere)
	AActivatableActor* ActivatableActor;
#pragma endregion



};
