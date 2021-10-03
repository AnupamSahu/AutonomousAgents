// Copyright Epic Games, Inc. All Rights Reserved.

#include "InterceptionTask.h"

#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

EBTNodeResult::Type UInterceptionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(IsValid(Agent) && IsValid(Target) && MovementComponent != nullptr)
	{
		//DrawDebugSphere(GetWorld(), Agent->GetActorLocation(), 50.0f, 32, FColor::Red, false, -1, 0, 2.5f);

		// Predict New Location
		const FVector& TargetLocation = Target->GetActorLocation();
		const FVector& TargetVelocity = Target->GetVelocity();

		// Get Agent's stats
		const FVector& AgentVelocity = Agent->GetVelocity();
		const FVector& AgentLocation = Agent->GetActorLocation();

		// Velocity of the Agent from its Frame-of-Reference
		const FVector& RelativeVelocity = TargetVelocity - AgentVelocity;

		// Distance between the Agent and the Target in the Initial Frame-of-Reference
		const float Separation = FVector::Dist(TargetLocation, AgentLocation);
		// Time it would take to reach the Target
		const float TimeToClose = Separation / (RelativeVelocity.Size() + SMALL_NUMBER);

		// The location the Target would have moved to by the time the Agent reached the original location
		const FVector& NewLocation = TargetLocation + TargetVelocity * TimeToClose;

		// -----------------------------------------------------------------------------

		// Find the velocity required to reach the NewLocation
		const FVector& DesiredVelocity = (NewLocation - Agent->GetActorLocation()).GetSafeNormal() * MovementComponent->GetMaxSpeed();

		// Calculate the required Steering Force
		const FVector& SteerForce = DesiredVelocity - Agent->GetVelocity();
		MovementForce += SteerForce;
		// -------------------------
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("MovementForce", MovementForce);

	return EBTNodeResult::Succeeded;
}

void UInterceptionTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	// Do nothing else
}
