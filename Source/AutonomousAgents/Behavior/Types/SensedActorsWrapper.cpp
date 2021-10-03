// Copyright Epic Games, Inc. All Rights Reserved.


#include "SensedActorsWrapper.h"

#include "Perception/AISenseConfig_Sight.h"

void USensedActorsWrapper::SenseNeighbors(UAIPerceptionComponent* AIPerceptionTarget, float SightRadius, float LoseSightRadius, float PeripheralVisionHalfAngle)
{
	if(AIPerceptionTarget != nullptr)
	{
		const FAISenseID& SightSenseID = UAISense::GetSenseID(UAISense_Sight::StaticClass());
		UAISenseConfig_Sight* AISenseConfig = Cast<UAISenseConfig_Sight>(AIPerceptionTarget->GetSenseConfig(SightSenseID));
		if(AISenseConfig != nullptr)
		{
			AISenseConfig->SightRadius = SightRadius;
			AISenseConfig->LoseSightRadius = LoseSightRadius;
			AISenseConfig->PeripheralVisionAngleDegrees = PeripheralVisionHalfAngle;

			AIPerceptionTarget->ConfigureSense(*AISenseConfig);
		}

		Neighbors.Reset();
		AIPerceptionTarget->RequestStimuliListenerUpdate();
		AIPerceptionTarget->GetCurrentlyPerceivedActors(AIPerceptionTarget->GetDominantSense(), Neighbors);
	}
}

AActor* USensedActorsWrapper::Get(uint32 ArrayIndex)
{
	if(Neighbors.IsValidIndex(ArrayIndex))
	{
		return Neighbors[ArrayIndex];
	}
	
	return nullptr;
}

uint32 USensedActorsWrapper::Num()
{
	return Neighbors.Num();
}
