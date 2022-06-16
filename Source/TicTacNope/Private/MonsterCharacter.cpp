// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterAIController.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick()  every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//this->GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	Trigger->InitCapsuleSize(55.f, 96.0f);;
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMonsterCharacter::OnBeginOverlap);

	//this is a bit weird, but having troubles getting the Aicontroller to grab the character refernce
	AMonsterAIController* AiController = Cast<AMonsterAIController>(GetController());

	if (AiController != NULL)
	{
		AiController->Character = this;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: Ai controller null"));
	}
}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMonsterCharacter::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString name = OtherActor->GetFullName();

	if (OtherActor->IsA<APlayerCharacter>())
	{
		APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
		HandleAttacking(player);
	}
	else if (OtherActor->IsA<ACell>())
	{
		ACell* cell = Cast<ACell>(OtherActor);
		HandleClaimingCell(cell);
	}
}

void AMonsterCharacter::UpdateMonsterState(MonsterStates UpdatedState)
{
	CurrentState = UpdatedState;

	switch (CurrentState)
	{
		case MonsterStates::WalkTowardsCell:
			GetCharacterMovement()->MaxAcceleration = WalkingSpeed;
			break;
		case MonsterStates::ChasePlayer:
			GetCharacterMovement()->MaxAcceleration = RunningSpeed;
	}
}

void AMonsterCharacter::HandleClaimingCell(ACell* Cell)
{
	if (Cell->CurrentState == CellStates::Empty)
	{
		Cell->CurrentState = CellStates::MonsterOccupied;
	}
	
	ATicTacNopeGameState* const gameState = GetWorld()->GetGameState<ATicTacNopeGameState>();
	gameState->Board->CheckBoardCompletion(Cell);

	//update the movement state
	UpdateMonsterState(MonsterStates::WalkTowardsCell);
}

void AMonsterCharacter::HandleAttacking(APlayerCharacter* Player)
{
	Player->PlayerTakeDamage(25);
}
