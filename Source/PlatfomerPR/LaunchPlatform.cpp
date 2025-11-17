// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPlatform.h"
#include "Components/BoxComponent.h"
#include"PlatfomerPRCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPlatform::ALaunchPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

}

// Called when the game starts or when spawned
void ALaunchPlatform::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPlatform::OnBeginOverlap);

}

// Called every frame
void ALaunchPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALaunchPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Display, TEXT("TriggerOn"));

	//충돌한것이 캐릭터

	APlatfomerPRCharacter* Character = Cast <APlatfomerPRCharacter>(OtherActor);
	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Not Character"));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT(" Character"));
	Character->LaunchCharacter(LaunchVelocity, true, true);


	if (HitSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
	}







}