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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SightRadius = 1000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float LoseSightRadius = 1555.0f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//float SightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float PeripheralDegrees = 130.0f;

private:

	/* Minimax algorithm used to determine the monster's next cell to move to*/
	UFUNCTION()
	void GetNextCell();

	UFUNCTION()
	int MiniMax(AGameBoard* board, ACell* cell, int Depth, bool IsMax);

	UPROPERTY()
	ACell* MoveToCell;

	UPROPERTY()
	APlayerCharacter* TargetToChase;

	UPROPERTY()
	UAIPerceptionComponent* AIPerceptionComponent;

};
