// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacNopeGameState.h"
#include "MonsterAIController.h"

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
	
	CurrentBoardState = BoardStates::Inactive;
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
		case BoardStates::InProgress:
			SetAiActivation(true);
			break;
		case BoardStates::MonsterVictory:
			UE_LOG(LogTemp, Warning, TEXT("MONSTER WINS!"));
			Board->ResetBoard();
			SetAiActivation(false);
			break;
		case BoardStates::PlayerVictory:
			UE_LOG(LogTemp, Warning, TEXT("PLAYER WINS!"));
			Board->ResetBoard();
			SetAiActivation(false);
			break;
		case BoardStates::PlayerMonsterDraw:
			UE_LOG(LogTemp, Warning, TEXT("DRAW!"));
			Board->ResetBoard();
			SetAiActivation(false);
			break;
	}

}


void ATicTacNopeGameState::SetAiActivation(bool active)
{
	UE_LOG(LogTemp, Warning, TEXT("Set AiActivation"));

	TArray<AActor*> FoundActors;
	AMonsterAIController* MonsterAi = NULL;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterAIController::StaticClass(), FoundActors);

	for (AActor* TActor : FoundActors)
	{
		MonsterAi = Cast<AMonsterAIController>(TActor);
	}

	if (MonsterAi != NULL)
	{
		if (!active)
		{
			MonsterAi->Reset();
		}
		else
		{
			MonsterAi->bCanBegin = true;
		}
	}
}