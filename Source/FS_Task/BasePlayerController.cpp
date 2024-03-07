// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "PlatformPawn.h"
#include <Net/UnrealNetwork.h>
#include "PlayerTeam.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APlatformPawn>(GetPawn());

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetGameInstance(), ScoreWidgetClass);
		ScoreWidget->AddToViewport();
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveY", this, &ABasePlayerController::Move);
}

void ABasePlayerController::Move(float AxisValue)
{
	if (!PlayerPawn) return;

	float Velocity = FMath::Clamp(AxisValue, -1.f, 1.f) * PawnSpeed;
	FVector Location = PlayerPawn->GetActorRightVector() * Velocity;

	PlayerPawn->AddActorLocalOffset(Location, true, 0, ETeleportType::TeleportPhysics);

	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		Server_UpdateMove(AxisValue);
	}
}

void ABasePlayerController::Server_UpdateMove_Implementation(float AxisValue)
{
	PlayerPawn = (!PlayerPawn) ? Cast<APlatformPawn>(GetPawn()) : PlayerPawn;

	float Velocity = FMath::Clamp(AxisValue, -1.f, 1.f) * PawnSpeed;
	FVector Location = PlayerPawn->GetActorRightVector() * Velocity;

	PlayerPawn->AddActorLocalOffset(Location, true, 0, ETeleportType::TeleportPhysics);

	PawnLocation = PlayerPawn->GetActorLocation();

	OnRep_PawnLocation();
}

void ABasePlayerController::OnRep_PawnLocation()
{
	PlayerPawn = (!PlayerPawn) ? Cast<APlatformPawn>(GetPawn()) : PlayerPawn;

	PlayerPawn->SetActorLocation(PawnLocation);
}

void ABasePlayerController::UpdateScoreWidget(int32 TeamOne, int32 TeamTwo)
{
	if (IsLocalController())
	{
		if (ScoreWidget)
		{
			FString TeamOneText = FString::Printf(TEXT("%d"), FMath::CeilToInt(TeamOne));
			FString TeamTwoText = FString::Printf(TEXT("%d"), FMath::CeilToInt(TeamTwo));

			ScoreWidget->TeamOneText->SetText(FText::FromString(TeamOneText));
			ScoreWidget->TeamTwoText->SetText(FText::FromString(TeamTwoText));
		}
	}
}

void ABasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasePlayerController, PawnLocation);
}
