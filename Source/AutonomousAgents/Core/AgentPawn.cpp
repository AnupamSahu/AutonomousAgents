// Copyright Epic Games, Inc. All Rights Reserved.

#include "AgentPawn.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AAgentPawn::AAgentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(GetRootComponent());

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovementComponent"));

	Velocity = FVector::ZeroVector;
	PreviousLocation = FVector::ZeroVector;
}

UFloatingPawnMovement* AAgentPawn::GetFloatingPawnMovementComponent() const
{
	return FloatingPawnMovement;
}

UStaticMeshComponent* AAgentPawn::GetStaticMesh() const
{
	return StaticMesh;
}

ELeaderType AAgentPawn::GetLeaderType()
{
	return LeaderType;
}
