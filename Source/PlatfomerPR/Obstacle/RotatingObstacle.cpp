// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingObstacle.h"
#include<Components/BoxComponent.h>
#include<PlatfomerPR/PlatfomerPRCharacter.h>
// Sets default values
ARotatingObstacle::ARotatingObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StaticMeshCom = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));
	HitComponent1 = CreateDefaultSubobject<UBoxComponent>(FName("HitCom1"));

	HitComponent1->SetupAttachment(StaticMeshCom);

}
FVector ARotatingObstacle::GetRotationAxis() const
{

	return RotationAxis;
}


// Called when the game starts or when spawned
void ARotatingObstacle::BeginPlay()
{
	Super::BeginPlay();
	HitComponent1->OnComponentBeginOverlap.AddDynamic(this, &ARotatingObstacle::OnBeginOverlap);
	HitComponent1->OnComponentEndOverlap.AddDynamic(this, &ARotatingObstacle::OnEndOverlap);
}

void ARotatingObstacle::Rotate(float DeltaTime)
{

	FRotator Rotator(RotationAxis.X, RotationAxis.Z, RotationAxis.Y);

	AddActorLocalRotation(Rotator * DeltaTime);



}

// Called every frame
void ARotatingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate(DeltaTime);



}


void ARotatingObstacle::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlatfomerPRCharacter* CharacterPlayer = Cast<APlatfomerPRCharacter>(OtherActor);
	if (CharacterPlayer)
	{
		CharacterPlayer->AddMovementInputObstacle(this);


	}



}

void ARotatingObstacle::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlatfomerPRCharacter* CharacterPlayer = Cast<APlatfomerPRCharacter>(OtherActor);
	if (CharacterPlayer)
	{
		CharacterPlayer->RemoveMovementInputObstacle(this);
	}
}

