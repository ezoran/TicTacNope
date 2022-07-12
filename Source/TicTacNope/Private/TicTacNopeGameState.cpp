// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacNopeGameState.h"
#include "MonsterAIController.h"
#include "AIController.h"
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

	ResetPlayerAndMonsterState();

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
			break;
		case BoardStates::MonsterVictory:
			UE_LOG(LogTemp, Warning, TEXT("MONSTER WINS!"));
			Board->ResetBoard();
			ResetPlayerAndMonsterState();
			break;
		case BoardStates::PlayerVictory:
			UE_LOG(LogTemp, Warning, TEXT("PLAYER WINS!"));
			Board->ResetBoard();
			ResetPlayerAndMonsterState();
			break;
		case BoardStates::PlayerMonsterDraw:
			UE_LOG(LogTemp, Warning, TEXT("DRAW!"));
			Board->ResetBoard();
			ResetPlayerAndMonsterState();
			break;
	}

}


void ATicTacNopeGameState::ResetPlayerAndMonsterState()
{
	APlayerCharacter* playerCharacter = NULL;
	AMonsterCharacter* monsterCharacter = NULL;
	AMonsterAIController* monsterAi = NULL;

	AActor* playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	playerCharacter = Cast<APlayerCharacter>(playerActor);

	AActor* monsterActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMonsterCharacter::StaticClass());
	monsterCharacter = Cast<AMonsterCharacter>(monsterActor);

	if (playerCharacter == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter cast failed"));
	}

	if (monsterCharacter == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("MonsterCharacter cast failed"));
	}

	if (monsterCharacter != NULL)
	{
		monsterAi = Cast<AMonsterAIController>(monsterCharacter->GetController());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MonsterAi cast failed"));
	}



	


	playerCharacter->Reset();
	monsterCharacter->Reset();
	monsterAi->Reset();

}

void ATicTacNopeGameState::CheckBoardCompletion(ACell* lastFilled)
{
	Board->CheckBoardCompletion(lastFilled);

	//broadcast the current board to update ui, etc
	if (OnCompletionChecked.IsBound())
	{
		OnCompletionChecked.Broadcast(Board);
	}
}

