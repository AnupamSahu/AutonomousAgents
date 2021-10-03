// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API AAgentController : public AAIController
{

	GENERATED_BODY()

protected:

	// Runs Behavior Tree, Finds Targets, Initializes blackboard
	virtual void BeginPlay() override;
	
public:
	virtual void GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const override;

protected:
	// A Behavior Tree that would drive this Agent's AI
	UPROPERTY(EditAnywhere, Category = "Behavior")
	UBehaviorTree* BehaviorTree = nullptr;

};
