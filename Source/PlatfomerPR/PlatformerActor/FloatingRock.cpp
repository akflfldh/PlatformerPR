// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingRock.h"
#include"Components/SphereComponent.h"

// Sets default values
AFloatingRock::AFloatingRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));
	//	StaticMeshComponent->SetupAttachment();


	FloatingDownTriggerComponent = CreateDefaultSubobject<USphereComponent>(FName("FloatingDownTriggerCom"));
	FloatingDownTriggerComponent->SetupAttachment(StaticMeshComponent);


}

// Called when the game starts or when spawned
void AFloatingRock::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();


	if (FloatingDownTriggerComponent)
	{
		FloatingDownTriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AFloatingRock::OnBeginOverlapFloatingDown);
		FloatingDownTriggerComponent->OnComponentEndOverlap.AddDynamic(this, &AFloatingRock::OnEndOverlapFloatingDown);
	}
}

void AFloatingRock::OnBeginOverlapFloatingDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	bFloatingDown = true;


}

void AFloatingRock::OnEndOverlapFloatingDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	bFloatingDown = false;

}

// Called every frame
void AFloatingRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Floating(DeltaTime);
}

void AFloatingRock::Floating(float DeltaTime)
{
	FVector Location = GetActorLocation();
	if (bFloatingDown == false)
	{


		Location.Z += DeltaTime * FloatingSpeed * FloatingDIr;

		if (Location.Z >= (StartLocation.Z + FloatingDistance) && (FloatingDIr == 1))
		{
			FloatingDIr = -1;
		}
		else if ((Location.Z <= (StartLocation.Z - FloatingDistance)) && (FloatingDIr == -1))
		{
			FloatingDIr = 1;
		}
	}
	else
	{
		Location.Z += DeltaTime * FloatingDownSpeed * -1;
		if (Location.Z < (StartLocation.Z - FloatingDistance))
		{
			Location.Z = StartLocation.Z - FloatingDistance;
		}
		FloatingDIr = 1;
	}

	SetActorLocation(Location);

}



