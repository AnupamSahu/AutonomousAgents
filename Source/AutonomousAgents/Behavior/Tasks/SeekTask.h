// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentBaseTask.h"
#include "SeekTask.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API USeekTask : public UAgentBaseTask
{
	GENERATED_BODY()

public:

	// Seeks the Target by applying a MovementForce based on the Target's location and the Agent's current Velocity
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Do Nothing
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

};
