// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "EquippableItem.generated.h"

/**
 *
 */
UENUM()
enum class EEquippableItemType :uint8
{
	eGroundItem = 0 UMETA(DisplayName = "GroundItem"),
	eFlyingItem = 1	 UMETA(DisplayName = "FlyingItem")

};


UCLASS()
class PLATFOMERPR_API AEquippableItem : public AItemActor
{
	GENERATED_BODY()



public:
	virtual void Tick(float DeltaTime) override;



	const TArray<FName>& GetSocketNameList() const;

	EEquippableItemType GetEquippableItemType() const;


protected:

	virtual void BeginPlay() override;



	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//범위에서 벗어남

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


private:


	UPROPERTY(EditAnywhere, Category = "Wear")
	TArray<FName> SocketNameList;

	/*UPROPERTY(VisibleAnywhere, Category = "Wear")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Wear")
	UStaticMesh* Mesh;*/

	UPROPERTY(EditAnywhere, Category = "Wear")
	EEquippableItemType EquippableItemType;

};
