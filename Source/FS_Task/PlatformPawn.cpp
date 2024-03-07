// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseGameMode.h"
#include "BasePlayerController.h"

APlatformPawn::APlatformPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(GetRootComponent());

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetRootComponent());
	PlayerCamera->SetWorldLocation(FVector(0.f, 0.f,3000.f));
	PlayerCamera->SetWorldRotation(FRotator(-90.0f, 0.0f, -90.f));
}

void APlatformPawn::BeginPlay()
{
	Super::BeginPlay();
	
	ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
	if (GameMode)
	{
		GameMode->OnTeamScore.AddDynamic(this, &APlatformPawn::UpdateScore);
	}
}

void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformPawn::UpdateScore(int32 TeamOne, int32 TeamTwo)
{
	Server_ScoreWidget(TeamOne, TeamTwo);
}

void APlatformPawn::Server_ScoreWidget_Implementation(int32 TeamOne, int32 TeamTwo)
{
	RPCScoreWidget(TeamOne, TeamTwo);
}

void APlatformPawn::RPCScoreWidget_Implementation(int32 TeamOne, int32 TeamTwo)
{
	ABasePlayerController* BasePlayerController = GetController<ABasePlayerController>();

	if (BasePlayerController)
	{
		BasePlayerController->UpdateScoreWidget(TeamOne, TeamTwo);
	}
}


