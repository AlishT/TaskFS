// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTeam.h"
#include "BasePlayerController.generated.h"

class APlatformPawn;
class UScoreWidget;
/**
 * 
 */
UCLASS()
class FS_TASK_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(Transient)
	APlatformPawn* PlayerPawn = nullptr;

	UPROPERTY(ReplicatedUsing = OnRep_PawnLocation)
	FVector PawnLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerPawn")
	float PawnSpeed = 0.f;

	void Move(float AxisValue);

	UFUNCTION(Server, reliable)
	void Server_UpdateMove(float AxisValue);

	UFUNCTION()
	void OnRep_PawnLocation();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Players Score")
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	UScoreWidget* ScoreWidget = nullptr;

	void UpdateScoreWidget(int32 TeamOne, int32 TeamTwo);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
