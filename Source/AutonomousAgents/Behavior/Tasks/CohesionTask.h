// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentSensingBaseTask.h"
#include "CohesionTask.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API UCohesionTask : public UAgentSensingBaseTask
{
	GENERATED_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:
	
	// Decides the strength of following a group's location, 1 = Full Cohesion, 0 = No Cohesion, Between 0 and 1 = Partial Cohesion
	UPROPERTY(EditAnywhere, Category = "Agent Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float CohesionBias = 1.0f;
	
};
