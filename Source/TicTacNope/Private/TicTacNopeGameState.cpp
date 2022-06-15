// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacNopeGameState.h"

ATicTacNopeGameState::ATicTacNopeGameState()
{

}

void ATicTacNopeGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();
	
	// spoawn a game board at world location 0,0,0 - it's BeginPlay handles fetching the cells in the scene
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	Board = GetWorld()->SpawnActor<AGameBoard>(Location, Rotation);
	
	//TODO: commenting out for now
	//CurrentBoardState = BoardStates::Inactive;
	CurrentBoardState = BoardStates::InProgress;
}

void ATicTacNopeGameState::UpdateBoardState(BoardStates InState)
{
	CurrentBoardState = InState;

	if (OnStateModified.IsBound())
	{
		OnStateModified.Broadcast(CurrentBoardState);
	}

	//check for a victory
	switch (CurrentBoardState)
	{
		case BoardStates::MonsterVictory:
			UE_LOG(LogTemp, Warning, TEXT("MONSTER WINS BITCH!"));
			break;
		case BoardStates::PlayerVictory:
			UE_LOG(LogTemp, Warning, TEXT("PLAYER WINS!"));
			break;
		case BoardStates::PlayerMonsterDraw:
			UE_LOG(LogTemp, Warning, TEXT("DRAW!"));
			break;
	}

}