// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "UObject/NoExportTypes.h"
#include "SensedActorsWrapper.generated.h"

// Forward declarations
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API USensedActorsWrapper : public UObject
{
	GENERATED_BODY()

public:
	
	// Refreshes the Neighbors array with the Actors currently perceived by the Target AIPerception Component
	void SenseNeighbors(UAIPerceptionComponent* AIPerceptionTarget, float SightRadius, float LoseSightRadius, float PeripheralVisionHalfAngle);

	// Returns an Actor reference from the Neighbors array
	// ArrayIndex : Should be a valid Array position
	AActor* Get(uint32 ArrayIndex);	

	// Returns the total length of the Neighbors Array
	uint32 Num();
	
protected:

	// An Array containing all currently perceived Actors
	UPROPERTY()
	TArray<AActor*> Neighbors;
	
};