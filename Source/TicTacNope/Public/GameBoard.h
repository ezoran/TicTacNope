// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Cell.h"
#include "GameBoard.generated.h"

UCLASS()
class TICTACNOPE_API AGameBoard : public AActor
{
	GENERATED_BODY()

public:

	AGameBoard();

	UPROPERTY()
	TArray<ACell*> CurrentCells;

	/* Called when a cell has been filled*/
	UFUNCTION()
	void CheckBoardCompletion(ACell* lastFilled);

	UFUNCTION()
	BoardStates GetBoardState(ACell* lastFilled);

	/* Populate CurrentCells by searching the scene for all cell objects*/
	UFUNCTION(BlueprintCallable)
	void FetchAllCells();


	UFUNCTION()
	void ResetBoard();

private:

	/* From the last triggered cell, check the cell's row */
	UFUNCTION()
	bool CheckForDraw();

	/* From the last triggered cell, check the cell's row */
	UFUNCTION()
	bool CheckForHorizontalWin(ACell* lastFilled);

	/* From the last triggered cell, check the cell's column*/
	UFUNCTION()
	bool CheckForVerticalWin(ACell* lastFilled);

	/* From the last triggered cell, check the diagonal */
	UFUNCTION()
	bool CheckForDiagonalWin(ACell* lastFilled);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
