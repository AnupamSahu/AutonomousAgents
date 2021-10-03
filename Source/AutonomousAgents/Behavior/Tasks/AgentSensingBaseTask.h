// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgentBaseTask.h"
#include "AgentSensingBaseTask.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API UAgentSensingBaseTask : public UAgentBaseTask
{
	GENERATED_BODY()

protected:
	virtual void InitTask(UBehaviorTreeComponent& OwnerComp) override;

	// Maximum sight distance to notice a target
	UPROPERTY(EditAnywhere, Category = "Perception Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SightRadius = 100.0f;

	// Maximum sight distance to see target that has been already seen
	UPROPERTY(EditAnywhere, Category = "Perception Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LoseSightRadius = 101.0f;

	// How far to the side AI can see
	UPROPERTY(EditAnywhere, Category = "Perception Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "180.0", UIMax = "180.0"))
	float HalfFOV = 45.0f;
	
};
