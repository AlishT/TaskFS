// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerTeam.h"
#include "TeamStart.generated.h"

/**
 * 
 */
UCLASS()
class FS_TASK_API ATeamStart : public APlayerStart
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "PlayerTeam")
	EPlayerTeam PlayerTeam = EPlayerTeam::EPT_TeamOne;

public:
	FORCEINLINE EPlayerTeam GetPlayerTeam() { return PlayerTeam; }
};
