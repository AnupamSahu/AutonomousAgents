// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentSensingBaseTask.h"
#include "AlignmentTask.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API UAlignmentTask : public UAgentSensingBaseTask
{
	GENERATED_BODY()
public:
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	
	// Decides the strength of following a group's location, 1 = Full Cohesion, 0 = No Cohesion, Between 0 and 1 = Partial Cohesion
	UPROPERTY(EditAnywhere, Category = "Agent Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float AlignmentBias = 1.0f;
};
