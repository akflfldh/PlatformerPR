// Fill out your copyright notice in the Description page of Project Settings.


#include "SwingingObstacle.h"
#include<Components/BoxComponent.h>
#include<PlatfomerPR/PlatfomerPRCharacter.h>
// Sets default values
ASwingingObstacle::ASwingingObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));

	HitTriggerComponent = CreateDefaultSubobject<UBoxComponent>(FName("TriggerCom"));
	HitTriggerComponent->SetupAttachment(HitStaticMeshComponent);

}

// Called when the game starts or when spawned
void ASwingingObstacle::BeginPlay()
{
	Super::BeginPlay();
	HitTriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ASwingingObstacle::OnBeginOverlap);

}
void ASwingingObstacle::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{



	APlatfomerPRCharacter* Character = Cast<APlatfomerPRCharacter>(OtherActor);
	if (Character)
	{
		//캐릭터를 멀리 밀어내자

		float xScalar = 2000.0f * CurrentSwingdDir;
		Character->LaunchCharacter({ xScalar,0,2000 }, true, true);
	}

	//향후에는 어떤 회전방향 에서든 가능하도록 회전속도벡터와 위치벡터 외적을 이용해서 처리하자


}

// Called every frame
void ASwingingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float OffsetAngle = DeltaTime * SwingSpeed;

	if (CurrentSwingdDir == 1)
	{
		CurrentSwingAngle += OffsetAngle;

		if (CurrentSwingAngle >= MaxSwingAngle)
		{
			CurrentSwingAngle = MaxSwingAngle;
			CurrentSwingdDir *= -1;
		}

	}
	else if (CurrentSwingdDir == -1)
	{
		CurrentSwingAngle -= OffsetAngle;

		if (CurrentSwingAngle <= -MaxSwingAngle)
		{
			CurrentSwingAngle = -MaxSwingAngle;
			CurrentSwingdDir *= -1;
		}
	}

	FRotator Rotator(CurrentSwingAngle, 0, 0);
	SetActorRotation(Rotator);

}

