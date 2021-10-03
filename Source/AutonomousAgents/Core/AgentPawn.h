// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "AutonomousAgents/Behavior/Types/LeaderType.h"
#include "GameFramework/Pawn.h"
#include "AgentPawn.generated.h"

// Forward declaration
class UFloatingPawnMovement;

/*
 * 
 */
UCLASS()
class AUTONOMOUSAGENTS_API AAgentPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAgentPawn();

	// Returns a reference to the Pawn's FloatingPawnMovement Component
	UFloatingPawnMovement* GetFloatingPawnMovementComponent() const;

	// Returns a reference to the Pawn's StaticMesh Component
	UStaticMeshComponent* GetStaticMesh() const;

	// Returns the type of Leader this Agent can become 
	ELeaderType GetLeaderType();

protected:
	// The type of Leader this Agent can become
	UPROPERTY(EditAnywhere, Category = "Agent Settings")
	TEnumAsByte<ELeaderType> LeaderType;
	
protected:
	// A reference to the Pawn's StaticMesh Component
	UPROPERTY(VisibleDefaultsOnly, Category = "Agent Settings")
	UStaticMeshComponent* StaticMesh = nullptr;

	// A reference to the Pawn's FloatingPawnMovement Component
	UPROPERTY(VisibleDefaultsOnly, Category = "Agent Settings")
	UFloatingPawnMovement* FloatingPawnMovement = nullptr;
	
protected:
	// Contains the current velocity of the pawn, independent of the Movement Component
	FVector Velocity;

	// Stores the Location of the pawn in the last frame
	FVector PreviousLocation;
};
