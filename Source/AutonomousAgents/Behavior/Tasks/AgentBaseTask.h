// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AgentBaseTask.generated.h"

// Forward declarations
class USensedActorsWrapper;
class UStaticMeshComponent;
class UFloatingPawnMovement;

/**
 * 
 */
UCLASS(Abstract)
class AUTONOMOUSAGENTS_API UAgentBaseTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	// Do nothing
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	// Call InitTask(...)
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// Initialize components and read blackboard data
	virtual void InitTask(UBehaviorTreeComponent& OwnerComp);

protected:

	// A reference to the Pawn's FloatingPawnMovement Component
	UPROPERTY()
	UFloatingPawnMovement* MovementComponent = nullptr;

	// A reference to the Pawn's StaticMesh Component
	UPROPERTY()
	UStaticMeshComponent* StaticMesh = nullptr;

	// A reference to the Target Actor
	UPROPERTY()
	AActor* Target = nullptr;

	// A reference to the Agent Pawn on which the behavior is applied
	UPROPERTY()
	AActor* Agent = nullptr;

	// A reference to the Neighbors Wrapper contained in the BlackBoard
	UPROPERTY()
	USensedActorsWrapper* Neighbors = nullptr;
	
	// A vector containing the Movement Input Data
	FVector MovementForce;

};
