// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippableItem.h"
#include<PlatfomerPR/PlatfomerPRCharacter.h>

void AEquippableItem::BeginPlay()
{
	Super::BeginPlay();

	//StaticMeshCom = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));

}

void AEquippableItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{




}

void AEquippableItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


void AEquippableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);





}

const TArray<FName>& AEquippableItem::GetSocketNameList() const
{
	return SocketNameList;
	// TODO: 여기에 return 문을 삽입합니다.
}

EEquippableItemType AEquippableItem::GetEquippableItemType() const
{
	return EquippableItemType;
}
