// Copyright Epic Games, Inc. All Rights Reserved.

#include "AgentBaseTask.h"

#include "AIController.h"
#include "AutonomousAgents/Core/AgentPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AutonomousAgents/Behavior/Types/SensedActorsWrapper.h"


void UAgentBaseTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else.
}

EBTNodeResult::Type UAgentBaseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	InitTask(OwnerComp);

	return EBTNodeResult::Succeeded;
}

void UAgentBaseTask::InitTask(UBehaviorTreeComponent& OwnerComp)
{
	Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));

	Agent = OwnerComp.GetAIOwner()->GetPawn();
	if(IsValid(Agent))
	{
		AAgentPawn* AgentPawn = Cast<AAgentPawn>(Agent);
		if(AgentPawn != nullptr)
		{
			MovementComponent = AgentPawn->GetFloatingPawnMovementComponent();
			StaticMesh = AgentPawn->GetStaticMesh();
		}
	}

	Neighbors = Cast<USensedActorsWrapper>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Neighbors"));
	if(Neighbors == nullptr)
	{
		Neighbors = NewObject<USensedActorsWrapper>();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("Neighbors", Neighbors);
	}

	
	MovementForce = FVector::ZeroVector;
	MovementForce = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("MovementForce"));
}
