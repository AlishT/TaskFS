// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(GetRootComponent());

	bReplicates = true;
	SetReplicatingMovement(true);

	BallMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BallMovementComponent"));
	
	BallMovementComponent->bShouldBounce = true;
	BallMovementComponent->MaxSpeed = 3500.f;
	BallMovementComponent->InitialSpeed = 3500.f;
	BallMovementComponent->Bounciness = 1.f;
	BallMovementComponent->Friction = 0.f;
	BallMovementComponent->BounceVelocityStopSimulatingThreshold = 0.f;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::SpawnInDirection(const FVector& ShootDirection)
{
	BallMovementComponent->Velocity = ShootDirection * BallMovementComponent->InitialSpeed;
}

