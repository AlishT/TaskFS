// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerTeam.h"
#include "BaseGameMode.generated.h"

class ABall;
class ABasePlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamScore, int32, OneTeam, int32, TwoTeam);
/**
 * 
 */
UCLASS()
class FS_TASK_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "GameProperties")
	TSubclassOf<ABall> BallClass;

	bool bTeamOneFree = true;

	int32 TeamOneScore = 0;

	int32 TeamTwoScore = 0;

	UPROPERTY(EditDefaultsOnly, Category = "GameProperties")
	float SpawnAngle = 70.f;

protected:
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	FOnTeamScore OnTeamScore;

	void SpawnGameBall();

	void UpdateGameScore(EPlayerTeam Team);
};
