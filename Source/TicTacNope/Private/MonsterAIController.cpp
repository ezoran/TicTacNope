// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PerceptionComp"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	SightConfig->PeripheralVisionAngleDegrees = PeripheralDegrees;
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LoseSightRadius;
	//SightConfig->SetMaxAge(SightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	AIPerceptionComponent->ConfigureSense(*SightConfig);

	Character = Cast<AMonsterCharacter>(GetPawn());
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnPawnDetected);
}

void AMonsterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetToChase != NULL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Moving to player"));
		MoveToActor(TargetToChase, 5.0f);
	}
	else if (MoveToCell != NULL && MoveToCell->CurrentState == CellStates::Empty)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Moving to cell"));
		MoveToActor(MoveToCell, 5.0f);
	}
	else if(MoveToCell == NULL || MoveToCell->CurrentState != CellStates::Empty)
	{
		//don't have a cell target or a player chase target, grab the next best cell
		GetNextCell();
	}
}

void AMonsterAIController::OnPawnDetected(const TArray<AActor*>& UpdatedActors)
{

	int size = UpdatedActors.Num();

	UE_LOG(LogTemp, Warning, TEXT("pawns detected: %d"), size);

	for (AActor* Actor : UpdatedActors)
	{
		if(Actor->IsA<APlayerCharacter>())
		{
			TargetToChase = Cast<APlayerCharacter>(Actor);
		}
	}
}

void AMonsterAIController::GetNextCell()
{
	//UE_LOG(LogTemp, Warning, TEXT("GetNextCell called"));

	ATicTacNopeGameState* const gameState = GetWorld()->GetGameState<ATicTacNopeGameState>();

	if (gameState != NULL)
	{
		AGameBoard* b = gameState->Board;
		
		//first, check if we're starting with a fresh board, if so, pick a random starting point
		bool boardIsEmpty = true;
		TArray<int> potentialCellIndexes;

		for (int i = 0; i < b->CurrentCells.Num(); i++)
		{
			if (b->CurrentCells[i]->CurrentState != CellStates::Empty)
			{
				boardIsEmpty = false;
				return;
			}
		}

		if (boardIsEmpty)
		{
			MoveToCell = gameState->Board->CurrentCells[FMath::RandRange(0, b->CurrentCells.Num() - 1)];
		}
		else
		{
			//board not empty, commence with minimax selection
			int bestScore = -1000;

			for (int i = 0; i < b->CurrentCells.Num(); i++)
			{
				if (b->CurrentCells[i]->CurrentState == CellStates::Empty)
				{
					b->CurrentCells[i]->CurrentState = CellStates::MonsterOccupied;
					int score = MiniMax(b, b->CurrentCells[i], 0, false);

					if (score > bestScore)
					{
						bestScore = score;
						potentialCellIndexes.Empty();
					}
					else if (score == bestScore)
					{
						potentialCellIndexes.Add(i);
					}

					b->CurrentCells[i]->CurrentState = CellStates::Empty;
				}
			}

			int selectedIndex = potentialCellIndexes[FMath::RandRange(0, potentialCellIndexes.Num() - 1)];
			MoveToCell = b->CurrentCells[selectedIndex];

			UE_LOG(LogTemp, Warning, TEXT("Monster now moving to cell %d"), MoveToCell->CellId);
		}

	}
	else
	{
	}

}

/// <summary>
/// Minimax implementation to determine next move, 
/// I used the forum https://codereview.stackexchange.com/questions/268486/c-tic-tac-toe-ai-powered-by-minmax-algorithm
/// to help with having a minimax that didn't win every time
/// </summary>
int AMonsterAIController::MiniMax(AGameBoard* board, ACell* cell, int Depth, bool IsMax)
{
	int score = 0;

	//BoardStates state = b

	return score;
}




//TESTING: pick the first available
/*for (int i = 0; i < b->CurrentCells.Num(); i++)
{
	if (b->CurrentCells[i]->CurrentState == CellStates::Empty)
	{
		MoveToCell = gameState->Board->CurrentCells[i];
		break;
	}
}*/