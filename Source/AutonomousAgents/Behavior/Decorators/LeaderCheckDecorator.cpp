// Copyright Epic Games, Inc. All Rights Reserved.

#include "LeaderCheckDecorator.h"

#include "AIController.h"
#include "../Types/SensedActorsWrapper.h"
#include "BehaviorTree/BlackboardComponent.h"

void ULeaderCheckDecorator::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void ULeaderCheckDecorator::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

bool ULeaderCheckDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	USensedActorsWrapper* NeighborsWrapper = Cast<USensedActorsWrapper>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Neighbors"));
	if(NeighborsWrapper != nullptr)
	{
		NeighborsWrapper->SenseNeighbors(OwnerComp.GetAIOwner()->GetAIPerceptionComponent(), SightRadius, LoseSightRadius, HalfFOV);
		return NeighborsWrapper->Num()==0;
	}

	return false;
}
