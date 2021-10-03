// Copyright Epic Games, Inc. All Rights Reserved.


#include "SeekTask.h"

#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

EBTNodeResult::Type USeekTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(IsValid(Agent) && IsValid(Target) && MovementComponent != nullptr)
	{
		//DrawDebugSphere(GetWorld(), Agent->GetActorLocation(), 50.0f, 32, FColor::Red, false, -1, 0, 2.5f);

		const FVector& DesiredVelocity = (Target->GetActorLocation() - Agent->GetActorLocation()).GetSafeNormal() * MovementComponent->GetMaxSpeed();
		const FVector& SteerInput = DesiredVelocity - Agent->GetVelocity();
		MovementForce += SteerInput;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("MovementForce", MovementForce);
	return EBTNodeResult::Succeeded;
}

void USeekTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else.
}
