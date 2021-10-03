// Copyright Epic Games, Inc. All Rights Reserved.


#include "AgentSensingBaseTask.h"

#include "AIController.h"
#include "AutonomousAgents/Behavior/Types/SensedActorsWrapper.h"
#include "BehaviorTree/BlackboardComponent.h"

void UAgentSensingBaseTask::InitTask(UBehaviorTreeComponent& OwnerComp)
{
	Super::InitTask(OwnerComp);

	USensedActorsWrapper* NeighborsWrapper = Cast<USensedActorsWrapper>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Neighbors"));
	if(NeighborsWrapper != nullptr)
	{
		NeighborsWrapper->SenseNeighbors(OwnerComp.GetAIOwner()->GetAIPerceptionComponent(), SightRadius, LoseSightRadius, HalfFOV);
	}
}
