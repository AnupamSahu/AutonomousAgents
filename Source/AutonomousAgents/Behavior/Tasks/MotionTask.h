// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentBaseTask.h"
#include "MotionTask.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API UMotionTask : public UAgentBaseTask
{
	GENERATED_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
};
