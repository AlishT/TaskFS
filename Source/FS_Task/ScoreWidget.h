// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class FS_TASK_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* TeamOneText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* TeamTwoText = nullptr;
};
