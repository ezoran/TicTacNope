// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerCharacter.h"
#include "MonsterCharacter.h"
#include "TicTacNopeGameState.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MonsterAIController.generated.h"


UCLASS()
class TICTACNOPE_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:

	AMonsterAIController();

	AMonsterCharacter* Character;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void Reset();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	class UAISenseConfig_Sight* SightConfig;

private:

	/* Whenenever needed, updates MoveToCell so the AI has a next target*/
	UFUNCTION()
	void GetNextCell();

	UPROPERTY()
	ACell* MoveToCell;

	UPROPERTY()
	APlayerCharacter* TargetToChase;

	UPROPERTY()
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY()
	bool bCanBegin;

	UPROPERTY()
	float SightRadius = 500.0f;

	UPROPERTY()
	float LoseSightRadius = 550.0f;

	UPROPERTY()
	float SightAge = 5.0f;

	UPROPERTY()
	float PeripheralDegrees = 130.0f;
};
