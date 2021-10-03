// Copyright Epic Games, Inc. All Rights Reserved.

#include "AgentController.h"

#include "AgentPawn.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAgentController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	AActor* Target = nullptr;
	TArray<AActor*> SceneActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), TEXT("GroupChaseTarget"), SceneActors);

	if (SceneActors.Num() > 0)
	{
		Target = SceneActors[0];
	}

	if (Blackboard != nullptr)
	{
		Blackboard->SetValueAsObject("TargetActor", Target);

		AAgentPawn* Agent = Cast<AAgentPawn>(GetPawn());
		if(IsValid(Agent))
		{
			Blackboard->SetValueAsEnum("LeaderType", Agent->GetLeaderType());
		}
	}
}

void AAgentController::GetActorEyesViewPoint(FVector& Out_Location, FRotator& Out_Rotation) const
{
	APawn* CurrentPawn = GetPawn();
	if(IsValid(CurrentPawn))
	{
		Out_Location = CurrentPawn->GetActorLocation();
		Out_Rotation = CurrentPawn->GetActorForwardVector().Rotation();
	}
}
