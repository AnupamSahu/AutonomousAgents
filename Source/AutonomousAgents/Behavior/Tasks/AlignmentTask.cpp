// Copyright Epic Games, Inc. All Rights Reserved.


#include "AlignmentTask.h"

#include "AutonomousAgents/Behavior/Types/SensedActorsWrapper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

EBTNodeResult::Type UAlignmentTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(MovementComponent != nullptr && IsValid(Agent))
	{
		if(Neighbors->Num() > 0)
		{
			FVector FlockHeading = FVector::ZeroVector;
			int32 NumCounted = 0;

			for(uint32 i=0; i<Neighbors->Num(); ++i)
			{
				if(!IsValid(Neighbors->Get(i)))
				{
					continue;
				}

				FlockHeading += Neighbors->Get(i)->GetVelocity().GetSafeNormal();

				++NumCounted;
			}

			if (NumCounted > 0)
			{
				FlockHeading /= NumCounted;

				const FVector& DesiredVelocity = (FlockHeading - Agent->GetActorLocation()).GetSafeNormal() * MovementComponent->GetMaxSpeed();
				const FVector& AlignmentManeuver = DesiredVelocity - Agent->GetVelocity();

				MovementForce += AlignmentManeuver * AlignmentBias;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("MovementForce", MovementForce);
			}
		}
	}
	
	return EBTNodeResult::Succeeded;
}

void UAlignmentTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else
}
