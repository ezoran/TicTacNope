// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"
#include "TicTacNopeGameState.h"

AGameBoard::AGameBoard()
{
}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
	FetchAllCells();
}

void AGameBoard::FetchAllCells()
{
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACell::StaticClass(), FoundActors);

	for (AActor* TActor : FoundActors)
	{
		ACell* cell = Cast<ACell>(TActor);

		if (cell != nullptr)
			CurrentCells.Add(cell);
	}

	if (CurrentCells.Num() > 0)
	{
		//sort the array so it's ordered from 0-8
		Algo::SortBy(CurrentCells, &ACell::CellId);
	}
}

void AGameBoard::CheckBoardCompletion(ACell* lastFilled)
{
	BoardStates currentBoardState = BoardStates::InProgress;
	ATicTacNopeGameState* const gameState = GetWorld()->GetGameState<ATicTacNopeGameState>();
	
	gameState->UpdateBoardState(GetBoardState(lastFilled));

}

BoardStates AGameBoard::GetBoardState(ACell* lastFilled)
{
	BoardStates currentBoardState = BoardStates::InProgress;

	if (CheckForDraw())
	{
		currentBoardState = BoardStates::PlayerMonsterDraw;
	}
	else if (CheckForHorizontalWin(lastFilled) || CheckForVerticalWin(lastFilled) || CheckForDiagonalWin(lastFilled))
	{

		if (lastFilled->CurrentState == CellStates::MonsterOccupied)
		{
			currentBoardState = BoardStates::MonsterVictory;
		}
		else if (lastFilled->CurrentState == CellStates::PlayerOccupied)
		{
			currentBoardState = BoardStates::PlayerVictory;
		}
	}

	return currentBoardState;
}

bool AGameBoard::CheckForDraw()
{
	int filledCount = 0;

	for (int i = 0; i < CurrentCells.Num(); i++)
	{
		if (CurrentCells[i]->CurrentState != CellStates::Empty)
		{
			filledCount++;
		}
	}

	if (filledCount == CurrentCells.Num())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AGameBoard::CheckForHorizontalWin(ACell* lastFilled)
{
	bool hasWinner = false;

	if (CurrentCells[0]->CurrentState == lastFilled->CurrentState && CurrentCells[1]->CurrentState == lastFilled->CurrentState && CurrentCells[2]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}
	else if (CurrentCells[3]->CurrentState == lastFilled->CurrentState && CurrentCells[4]->CurrentState == lastFilled->CurrentState && CurrentCells[5]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}
	else if (CurrentCells[6]->CurrentState == lastFilled->CurrentState && CurrentCells[7]->CurrentState == lastFilled->CurrentState && CurrentCells[8]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}

	return hasWinner;
}

bool AGameBoard::CheckForVerticalWin(ACell* lastFilled)
{
	bool hasWinner = false;

	if (CurrentCells[0]->CurrentState == lastFilled->CurrentState && CurrentCells[3]->CurrentState == lastFilled->CurrentState && CurrentCells[6]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}
	else if (CurrentCells[1]->CurrentState == lastFilled->CurrentState && CurrentCells[4]->CurrentState == lastFilled->CurrentState && CurrentCells[7]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}
	else if (CurrentCells[2]->CurrentState == lastFilled->CurrentState && CurrentCells[5]->CurrentState == lastFilled->CurrentState && CurrentCells[8]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}

	return hasWinner;
}

bool AGameBoard::CheckForDiagonalWin(ACell* lastFilled)
{
	bool hasWinner = false;

	if (CurrentCells[0]->CurrentState == lastFilled->CurrentState && CurrentCells[4]->CurrentState == lastFilled->CurrentState && CurrentCells[8]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}
	else if (CurrentCells[2]->CurrentState == lastFilled->CurrentState && CurrentCells[4]->CurrentState == lastFilled->CurrentState && CurrentCells[6]->CurrentState == lastFilled->CurrentState)
	{
		hasWinner = true;
	}

	return hasWinner;
}

void AGameBoard::ResetBoard()
{
	for(int i = 0; i < CurrentCells.Num(); i++)
	{
		CurrentCells[i]->CurrentState = CellStates::Empty;
	}
}