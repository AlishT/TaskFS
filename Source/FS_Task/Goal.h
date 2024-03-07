// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerTeam.h"
#include "Goal.generated.h"

class UBoxComponent;

UCLASS()
class FS_TASK_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoal();

protected:
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default")
	EPlayerTeam PlayerTeam = EPlayerTeam::EPT_TeamOne;

	UFUNCTION()
	void OnBallOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
