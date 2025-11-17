// Fill out your copyright notice in the Description page of Project Settings.


#include "RoillingObstacle.h"
#include<PlatfomerPR/PlatfomerPRCharacter.h>
#include<Components/BoxComponent.h>
// Sets default values
ARoillingObstacle::ARoillingObstacle() :PlayerCharacter(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StaticMeshCom = CreateDefaultSubobject<UStaticMeshComponent>(FName("StatcMeshCom"));
	//StaticMeshCom->SetSimulatePhysics(true);


	ForceCom = CreateDefaultSubobject<UBoxComponent>(FName("ForceTriggerBoxCom"));

	ForceCom->SetupAttachment(StaticMeshCom);
}

void ARoillingObstacle::SetTargetLocation(const FVector& targetLocation)
{
	TargetLocation = targetLocation;
	DirWorld = TargetLocation - GetActorLocation();
	DirNormal = DirWorld.GetSafeNormal();

}

void ARoillingObstacle::SetSpeed(float speed)
{
	Speed = speed;
}

// Called when the game starts or when spawned
void ARoillingObstacle::BeginPlay()
{
	Super::BeginPlay();


	StartLocation = GetActorLocation();


	ForceCom->OnComponentBeginOverlap.AddDynamic(this, &ARoillingObstacle::OnBeginOverlap);
	ForceCom->OnComponentEndOverlap.AddDynamic(this, &ARoillingObstacle::OnEndOverlap);
}

void ARoillingObstacle::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlatfomerPRCharacter* Character = Cast< APlatfomerPRCharacter>(OtherActor);

	if (Character)
	{

		PlayerCharacter = Character;

	}



}
void ARoillingObstacle::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	PlayerCharacter = nullptr;

}

// Called every frame
void ARoillingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PreLocation = GetActorLocation();

	//start - > target location 죽 이동
	FVector Offset = DirNormal * DeltaTime * Speed;

	SetActorLocation(GetActorLocation() + Offset);

	float CurrentDistance = (GetActorLocation() - StartLocation).Length();

	float TargetDistance = (TargetLocation - StartLocation).Length();


	//회전
	//local
	StaticMeshCom->AddLocalRotation({ 0,5,0 });







	if (PlayerCharacter)
	{

		FVector LocationDelta = GetActorLocation() - PreLocation;
		FVector Velocity = LocationDelta / DeltaTime;
		PlayerCharacter->LaunchCharacter(Velocity, true, true);

	}

	if (CurrentDistance >= TargetDistance)
	{

		//
		Destroy();

	}



}

