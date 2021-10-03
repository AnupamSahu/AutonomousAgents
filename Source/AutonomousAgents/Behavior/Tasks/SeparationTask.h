// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentSensingBaseTask.h"
#include "SeparationTask.generated.h"

// Forward declarations
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API USeparationTask : public UAgentSensingBaseTask
{
	GENERATED_BODY()
public:

	// Sense all nearby actors, get their locations, calculate a vector to avoid to each nearby actor, apply the vector into MovementForce
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Do nothing
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:

	// Decides the strength of avoiding other Agents, 1 = Full Avoidance, 0 = No avoidance, Between 0 and 1 = Partial Avoidance
	UPROPERTY(EditAnywhere, Category = "Agent Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float AvoidanceBias = 1.0f;

};
