// Copyright Epic Games, Inc. All Rights Reserved.

#include "CohesionTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "AutonomousAgents/Behavior/Types/SensedActorsWrapper.h"

EBTNodeResult::Type UCohesionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(MovementComponent != nullptr && IsValid(Agent))
	{
		if(Neighbors->Num() > 0)
		{
			FVector FlockLocation = FVector::ZeroVector;
			int32 NumCounted = 0;

			for(uint32 i=0; i<Neighbors->Num(); ++i)
			{
				if(!IsValid(Neighbors->Get(i)))
				{
					continue;
				}

				FlockLocation += Neighbors->Get(i)->GetActorLocation();

				++NumCounted;
			}

			if (NumCounted > 0)
			{
				FlockLocation /= NumCounted;

				const FVector& DesiredVelocity = (FlockLocation - Agent->GetActorLocation()).GetSafeNormal() * MovementComponent->GetMaxSpeed();
				const FVector& CohesionManeuver = DesiredVelocity - Agent->GetVelocity();

				MovementForce += CohesionManeuver * CohesionBias;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("MovementForce", MovementForce);
			}
		}
	}

	return EBTNodeResult::Succeeded;
}

void UCohesionTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else.
}
