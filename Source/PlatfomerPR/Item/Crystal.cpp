// Fill out your copyright notice in the Description page of Project Settings.


#include "Crystal.h"
#include<Components/BoxComponent.h>
#include<PlatfomerPR/PlatformerGameMode.h>
#include<PlatfomerPR/PlatfomerPRCharacter.h>
#include<Kismet/GameplayStatics.h>
// Sets default values
ACrystal::ACrystal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(FName("TriggerCom"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));


	StaticMeshComponent->SetupAttachment(TriggerComponent);

}

// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ACrystal::OnBeginOverlap);


}

// Called every frame
void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatfomerPRCharacter* Characater = Cast<APlatfomerPRCharacter>(OtherActor);

	if (Characater == nullptr)
		return;

	//GameMode
	APlatformerGameMode* gameMode = Cast<APlatformerGameMode>(GetWorld()->GetAuthGameMode());

	if (gameMode)
	{
		gameMode->IncreaseCollectedCrystalCount();

		if (CrystalPickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CrystalPickupSound, GetActorLocation());
		}


		Destroy();

	}
}

