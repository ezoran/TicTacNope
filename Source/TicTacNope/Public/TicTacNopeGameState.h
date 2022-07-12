// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameBoard.h"
#include "GameFramework/GameStateBase.h"
#include "TicTacNopeGameState.generated.h"

class APlayerCharacter;
class AMonsterCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateModifiedSignature, const BoardStates&, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCompletionCheckedSignature, class AGameBoard*, Board);

UCLASS()
class TICTACNOPE_API ATicTacNopeGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	ATicTacNopeGameState();

	UFUNCTION(BlueprintCallable)
	void UpdateBoardState(BoardStates InState);

	UFUNCTION(BlueprintCallable)
	void ResetPlayerAndMonsterState();

	UPROPERTY(BlueprintReadWrite)
	AGameBoard* Board;

	UPROPERTY(BlueprintAssignable)
	FStateModifiedSignature OnStateModified;

	UPROPERTY(BlueprintAssignable)
	FCompletionCheckedSignature OnCompletionChecked;
	
	UFUNCTION()
	void CheckBoardCompletion(ACell* lastFilled);

private:

	UPROPERTY()
	BoardStates CurrentBoardState;

protected: 

	virtual void HandleBeginPlay() override;
};
