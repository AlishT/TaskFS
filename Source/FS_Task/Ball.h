// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class FS_TASK_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UStaticMeshComponent* BallMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* BallMovementComponent;

public:
	void SpawnInDirection(const FVector& ShootDirection);
};
