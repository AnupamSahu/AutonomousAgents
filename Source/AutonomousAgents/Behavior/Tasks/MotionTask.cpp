// Copyright Epic Games, Inc. All Rights Reserved.


#include "MotionTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

EBTNodeResult::Type UMotionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(MovementComponent != nullptr)
	{
		MovementComponent->AddInputVector(MovementForce);
		MovementForce = FVector::ZeroVector;
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("MovementForce", MovementForce);
	}

	return EBTNodeResult::Succeeded;
}

void UMotionTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else.
}
