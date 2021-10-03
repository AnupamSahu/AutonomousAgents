// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentBaseTask.h"
#include "InterceptionTask.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API UInterceptionTask : public UAgentBaseTask
{
	GENERATED_BODY()

public:

	// Get the Target's velocity, predict its location after DeltaTime, seek the predicted location
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	// Do nothing
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
};
