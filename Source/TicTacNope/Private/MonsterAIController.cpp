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

	bCanBegin = false;
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
	else if (MoveToCell == NULL || MoveToCell->CurrentState != CellStates::Empty)
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
			Character->UpdateMonsterState(MonsterStates::ChasePlayer);
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
		TArray<int> potentialCellIndexes;

		for (int i = 0; i < b->CurrentCells.Num(); i++)
		{
			if (b->CurrentCells[i]->CurrentState == CellStates::Empty)
			{
	
				potentialCellIndexes.Add(i);
			}
		}

		if (potentialCellIndexes.Num() > 0)
		{
			int selectedIndex = potentialCellIndexes[FMath::RandRange(0, potentialCellIndexes.Num() - 1)];
			MoveToCell = b->CurrentCells[selectedIndex];
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: could not get next AI move, board was null in GetNextMoves()"));

	}

}

void AMonsterAIController::Reset()
{
	UE_LOG(LogTemp, Error, TEXT("Reset Ai"));

	//reset any ai related stuff when not in game
	bCanBegin = false;
	MoveToCell = NULL;
	TargetToChase = NULL;


}