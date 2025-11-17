// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include"LogHelper.h"
#include "EnhancedInputSubsystems.h"
#include"StageActor.h"
#include "StageSelectActor.h"
#include<Kismet/GameplayStatics.h>

// Sets default values
AStageSelectCameraPawn::AStageSelectCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("CameraCom"));
}

// Called when the game starts or when spawned
void AStageSelectCameraPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AStageSelectCameraPawn::LeftMoveStage()
{
	PrintLog("LeftMove");


	if (CurrentStageIndex == 0)
		return;

	CurrentStageIndex -= 1;
	SetSelectStageLocation();

}

void AStageSelectCameraPawn::RightMoveStage()
{
	PrintLog("RightMove");
	if (CurrentStageIndex == StageActorList.Num() - 1)
		return;

	CurrentStageIndex += 1;
	SetSelectStageLocation();
}

void AStageSelectCameraPawn::EnterStage()
{

	if (StageActorList.IsEmpty())
		return;

	if (CurrentStageIndex >= StageActorList.Num())
		return;



	FString stageLevelName = StageActorList[CurrentStageIndex]->GetStageName();
	UGameplayStatics::OpenLevel(this, FName(stageLevelName));


}

// Called every frame
void AStageSelectCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStageSelectCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {


		EnhancedInputComponent->BindAction(LeftArrowAction, ETriggerEvent::Started, this, &AStageSelectCameraPawn::LeftMoveStage);
		EnhancedInputComponent->BindAction(RightArrowAction, ETriggerEvent::Started, this, &AStageSelectCameraPawn::RightMoveStage);
		EnhancedInputComponent->BindAction(EnterAction, ETriggerEvent::Started, this, &AStageSelectCameraPawn::EnterStage);
	}



}

void AStageSelectCameraPawn::PossessedBy(AController* NewController)
{

	if (APlayerController* PlayerController = Cast<APlayerController>(NewController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{

			if (InputMappingContext)
			{

				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}


	}

}

void AStageSelectCameraPawn::SetSelectStageLocation()
{

	if (StageSelectActor)
	{
		FVector StageLocation = StageActorList[CurrentStageIndex]->GetActorLocation();

		FVector SelectStageLocation = StageLocation;
		SelectStageLocation.Z = StageSelectActor->GetActorLocation().Z;

		StageSelectActor->SetActorLocation(SelectStageLocation);

	}



}

