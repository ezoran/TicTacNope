// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick()  every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//this->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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
	UE_LOG(LogTemp, Warning, TEXT("Collided with %s"), *name);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Monster Capsule Hit Something!"));

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
			//GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			break;
		case MonsterStates::ChasePlayer:
			//GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
		case MonsterStates::FillingCell:
			//some animation?
			break;
		case MonsterStates::AttackingPlayer:
			//some animation
			break;
	}
}

void AMonsterCharacter::HandleClaimingCell(ACell* Cell)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Monster is now filling cell"));

	//TODO: add time delay here
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Monster is now Attacking"));
	Player->PlayerTakeDamage(25);

}
