// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPortal.h"
#include "Components/BoxComponent.h"
#include"PlatfomerPRCharacter.h"
#include"Kismet/GameplayStatics.h"
// Sets default values
ALevelPortal::ALevelPortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));


}

// Called when the game starts or when spawned
void ALevelPortal::BeginPlay()
{
	Super::BeginPlay();


	if (TriggerComponent)
	{
		TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelPortal::OnBeginOverlap);

	}

}

// Called every frame
void ALevelPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



bool ALevelPortal::CanEnterNextLevel() const
{

	return true;


}


void ALevelPortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlatfomerPRCharacter* Character = Cast <APlatfomerPRCharacter>(OtherActor);
	if (Character != nullptr)
	{
		if (CanEnterNextLevel())
		{
			UGameplayStatics::OpenLevel(this, FName(NextLevel));

		}


	}
}

FString ALevelPortal::GetNextLevelStr() const
{
	return NextLevel;
}
