// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include<Components/BoxComponent.h>
// Sets default values
AItemActor::AItemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	OverlapCom = CreateDefaultSubobject<UBoxComponent>(FName("BoxCom"));

	StaticMeshCom = CreateDefaultSubobject < UStaticMeshComponent>(FName("RootStaticMeshCom"));

	OverlapCom->SetupAttachment(StaticMeshCom);

	RootComponent = StaticMeshCom;
}

const UStaticMeshComponent* AItemActor::GetStaticMeshComponent() const
{
	return StaticMeshCom;
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();


	OverlapCom->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnBeginOverlap);
	OverlapCom->OnComponentEndOverlap.AddDynamic(this, &AItemActor::OnEndOverlap);


}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AItemActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{



}

void AItemActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{




}