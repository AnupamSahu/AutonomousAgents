// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeparationTask.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "AutonomousAgents/Behavior/Types/SensedActorsWrapper.h"

EBTNodeResult::Type USeparationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(IsValid(Agent) && MovementComponent != nullptr)
	{
		if (Neighbors->Num() > 0)
		{
			FVector AgentLocation = Agent->GetActorLocation();
			FVector AverageAvoidance = FVector::ZeroVector;
			int32 NumCounted = 0;

			for (uint32 i = 0; i < Neighbors->Num(); ++i)
			{
				if(!IsValid(Neighbors->Get(i)))
				{
					continue;
				}

				const FVector& NeighborVector = Neighbors->Get(i)->GetActorLocation() - AgentLocation;

				const FVector& AvoidanceDirection = -NeighborVector.GetSafeNormal();
				const float Separation = NeighborVector.Size();

				AverageAvoidance += AvoidanceDirection / Separation;

				++NumCounted;
			}

			if (NumCounted > 0)
			{
				AverageAvoidance /= NumCounted;
				AverageAvoidance.Normalize();
				const FVector& AvoidanceInput = AverageAvoidance * MovementComponent->GetMaxSpeed() - Agent->GetVelocity();

				MovementForce += AvoidanceInput * AvoidanceBias;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("MovementForce", MovementForce);
			}
		}
	}
	return EBTNodeResult::Succeeded;
}

void USeparationTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else.
}
