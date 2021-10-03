// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentBaseTask.h"
#include "RotationTask.generated.h"

/**
 *
 */
UCLASS()
class AUTONOMOUSAGENTS_API URotationTask : public UAgentBaseTask
{
	GENERATED_BODY()
public:

	// Align the Agent towards its velocity
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Do nothing
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// Defines how fast the Agent aligns with its own velocity
	UPROPERTY(EditAnywhere, Category = "Movement Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "100.0", UIMax = "100.0"))
	float TurningSpeed;
};
