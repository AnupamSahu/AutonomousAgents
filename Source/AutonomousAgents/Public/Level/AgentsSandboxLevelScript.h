// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "AgentsSandboxLevelScript.generated.h"

// Forward declarations
class USpatialGridSubsystem;
class UBaseAutonomousBehaviour;
class UAgentSpawnerConfig;
class AAgentPawn;

/**
 * 
 */
UCLASS(Blueprintable)
class AUTONOMOUSAGENTS_API AAgentsSandboxLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	AAgentsSandboxLevelScript();
	
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnActorsImmediately(const UAgentSpawnerConfig* SpawnConfig);

	UFUNCTION(BlueprintCallable)
	void DestroyAllSpawnedActors();

	UFUNCTION(BlueprintCallable)
	void ScaleBehaviourInfluence(TSubclassOf<UBaseAutonomousBehaviour> TargetBehaviour, float Scale);

	UFUNCTION(BlueprintCallable)
	void ResetBehaviourInfluence(TSubclassOf<UBaseAutonomousBehaviour> TargetBehaviour);

	UFUNCTION(BlueprintCallable)
	void PutActorIntoGrid(AActor* Actor) const;

protected:
	
	virtual void BeginPlay() override;

private:
	
	TArray<TWeakObjectPtr<AAgentPawn>> SpawnedAgents;

	UPROPERTY()
	TObjectPtr<USpatialGridSubsystem> SpatialGridSubsystem;
};
