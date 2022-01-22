// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    float Speed = 15.f;

    UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
    FVector TargetLocation;

    void AddActiveTrigger();
    void RemoveActiveTrigger();

private:
    FVector GlobalTargetLocation;
    FVector GlobalStartLocation;

    UPROPERTY(EditAnywhere)
    int ActiveTriggers = 1;

public:
    AMovingPlatform();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

};
