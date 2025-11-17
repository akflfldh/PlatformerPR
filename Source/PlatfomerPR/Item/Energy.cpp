// Fill out your copyright notice in the Description page of Project Settings.


#include "Energy.h"
#include<Components/BoxComponent.h>
#include<PlatfomerPR/GameMode/StartStageGameMode.h>
#include<PlatfomerPR/PlatfomerPRCharacter.h>
#include<Kismet/GameplayStatics.h>
// Sets default values
AEnergy::AEnergy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(FName("TriggerCom"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));


	StaticMeshComponent->SetupAttachment(TriggerComponent);


}

// Called when the game starts or when spawned
void AEnergy::BeginPlay()
{
	Super::BeginPlay();
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnergy::OnBeginOverlap);


}

// Called every frame
void AEnergy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnergy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatfomerPRCharacter* Characater = Cast<APlatfomerPRCharacter>(OtherActor);

	if (Characater == nullptr)
		return;

	//GameMode
	AStartStageGameMode* gameMode = Cast<AStartStageGameMode>(GetWorld()->GetAuthGameMode());

	if (gameMode)
	{
		gameMode->IncreaseEnergy();

		if (PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		}

		Destroy();

	}
}