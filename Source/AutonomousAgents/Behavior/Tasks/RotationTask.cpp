// Copyright Epic Games, Inc. All Rights Reserved.


#include "RotationTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type URotationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void URotationTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	Super::InitTask(OwnerComp);

	if (IsValid(Agent) && MovementComponent != nullptr)
	{
		// Create a New Rotation from the Agent's Velocity and apply it to the Agent's Actor

		const FRotator& TargetRotation = Agent->GetVelocity().GetSafeNormal().Rotation();
		const FRotator& CurrentRotation = Agent->GetActorRotation();

		const FRotator& DeltaRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, TurningSpeed);

		Agent->SetActorRotation(DeltaRotation);
	}
}

void URotationTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else.
}


