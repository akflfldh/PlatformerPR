#pragma once
#include"LogHelper.h"
#include "CoreMinimal.h"


void PrintLog(const FString& text)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *text);
}