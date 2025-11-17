// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseButton.h"
#include "Components/BoxComponent.h"
#include"PlatfomerPRCharacter.h"
#include"ActivatableActor.h"
// Sets default values
ABaseButton::ABaseButton() :ActivatableActor(nullptr), bInRange(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	DetactComponent = CreateDefaultSubobject<UBoxComponent>(FName("DetactComponent"));



}

void ABaseButton::OnPress()
{
	//triggetActor의 OnTrigger호출
	if (ActivatableActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Print"));
		ActivatableActor->OnActivate();
	}

}



// Called when the game starts or when spawned
void ABaseButton::BeginPlay()
{
	Super::BeginPlay();

	if (DetactComponent)
	{
		DetactComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseButton::OnBeginOverlap);
		DetactComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseButton::OnEndOverlap);
	}
}



// Called every frame
void ABaseButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseButton::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlatfomerPRCharacter* Character = Cast<APlatfomerPRCharacter>(OtherActor);

	if (Character)
	{
		//bInRange = true;
		Character->AddButton(this);


		UE_LOG(LogTemp, Display, TEXT("InRegion"));
	}

}

void ABaseButton::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	//bInRange = false;

	APlatfomerPRCharacter* Character = Cast<APlatfomerPRCharacter>(OtherActor);

	if (Character)
	{
		//bInRange = true;
		Character->RemoveButton(this);
	}
}
