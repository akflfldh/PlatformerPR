// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthZeroDeletegate);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLATFOMERPR_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	//체력이 0이되었을떄 호출될 델리케이트 
	FOnHealthZeroDeletegate OnHealthZero;


	void SetMaxHealth(int health);
	void SetCurrentHealth(int health);

	int GetMaxHealth() const;
	int GetCurrentMaxHealth() const;


	void TakeDamage(int DamageAmount);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int CurrentHealth;



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
