﻿
#include "Behaviours/DirectSeekBehaviour.h"
#include "Core/Agent.h"

FVector UDirectSeekBehaviour::CalculateSeekForce(const UAgent* AffectedAgentData, const AActor* ChaseTarget, const float MaxSpeed) const
{
	if(!bIsEnabled || !ChaseTarget)
	{
		return FVector::ZeroVector;
	}
	
	FVector DesiredVelocity = ChaseTarget->GetActorLocation() - AffectedAgentData->Location;
	
	DesiredVelocity.Normalize();
	DesiredVelocity *= MaxSpeed;

	const FVector& ChaseManeuver = DesiredVelocity - AffectedAgentData->Velocity;
	
	return ChaseManeuver * Influence * InfluenceScale;
}
