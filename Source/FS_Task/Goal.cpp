// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Components/BoxComponent.h"
#include "PlayerTeam.h"
#include "Ball.h"
#include "BaseGameMode.h"

// Sets default values
AGoal::AGoal()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnBallOverlap);

}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoal::OnBallOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor->IsA(ABall::StaticClass()))
	{
		ABall* GameBall = Cast<ABall>(OtherActor);

		if (GameBall)
		{
			GameBall->Destroy();
		}

		ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
		if (GameMode)
		{
			GameMode->UpdateGameScore(PlayerTeam);
			GameMode->SpawnGameBall();
		}
	}
}

