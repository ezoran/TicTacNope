// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameBoard.h"
#include "GameFramework/GameStateBase.h"
#include "TicTacNopeGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateModifiedSignature, const BoardStates&, State);

UCLASS()
class TICTACNOPE_API ATicTacNopeGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	ATicTacNopeGameState();

	UFUNCTION(BlueprintCallable)
	void UpdateBoardState(BoardStates InState);

	UFUNCTION(BlueprintCallable)
	void SetAiActivation(bool active);

	UPROPERTY(BlueprintReadWrite)
	AGameBoard* Board;

	UPROPERTY(BlueprintAssignable)
	FStateModifiedSignature OnStateModified;

private:

	UPROPERTY()
	BoardStates CurrentBoardState;

protected: 

	virtual void HandleBeginPlay() override;
};
