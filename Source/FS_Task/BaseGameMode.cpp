// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"
#include "PlayerTeam.h"
#include "Ball.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformPawn.h"
#include "TeamStart.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "BasePlayerController.h"

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!NewPlayer) return;

	APlatformPawn* NewPlatformPawn = Cast<APlatformPawn>(NewPlayer->GetPawn());

	if (NewPlatformPawn)
	{
		if (bTeamOneFree) 
		{
			NewPlatformPawn->SetPlayerTeam(EPlayerTeam::EPT_TeamOne);
			
			bTeamOneFree = false;

			UE_LOG(LogTemp, Warning, TEXT("Waiting for another player"));
		}
		else
		{
			NewPlatformPawn->SetPlayerTeam(EPlayerTeam::EPT_TeamTwo);
			
			SpawnGameBall();
		}

		for (TActorIterator<ATeamStart> TeamStartItr(GetWorld()); TeamStartItr; ++TeamStartItr)
		{
			if (NewPlatformPawn->GetPlayerTeam() == TeamStartItr->GetPlayerTeam())
			{
				FVector StartLocation = TeamStartItr->GetActorLocation();
				NewPlatformPawn->SetActorLocation(StartLocation);
			}
		}
	}
}

void ABaseGameMode::SpawnGameBall()
{
	if (!BallClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	float DirectionScatter = FMath::RandRange(-SpawnAngle, SpawnAngle);
	FRotator SpawBallRotator = FRotator(0.f, DirectionScatter, 0.f);

	ABall* GameBall = GetWorld()->SpawnActor<ABall>(BallClass, FVector(0.f, 0.f, 150.f), SpawBallRotator, SpawnParams);

}

void ABaseGameMode::UpdateGameScore(EPlayerTeam Team)
{
	switch (Team)
	{
	case EPlayerTeam::EPT_TeamOne:
		TeamTwoScore++;
		break;
	case EPlayerTeam::EPT_TeamTwo:
		TeamOneScore++;
		break;
	}

	OnTeamScore.Broadcast(TeamOneScore, TeamTwoScore);
}
