// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerTeam.h"
#include "PlatformPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;

UCLASS()
class FS_TASK_API APlatformPawn : public APawn
{
	GENERATED_BODY()

public:
	APlatformPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UStaticMeshComponent* PlatformMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default")
	UCameraComponent* PlayerCamera = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default")
	EPlayerTeam PlayerTeam = EPlayerTeam::EPT_TeamOne;

	UFUNCTION()
	void UpdateScore(int32 TeamOne, int32 TeamTwo);

	UFUNCTION(Server, reliable)
	void Server_ScoreWidget(int32 TeamOne, int32 TeamTwo);

	UFUNCTION(Client, reliable)
	void RPCScoreWidget(int32 TeamOne, int32 TeamTwo);

public:
	FORCEINLINE EPlayerTeam GetPlayerTeam() const { return PlayerTeam; }
	FORCEINLINE void SetPlayerTeam(EPlayerTeam Team) {PlayerTeam = Team;}
};
