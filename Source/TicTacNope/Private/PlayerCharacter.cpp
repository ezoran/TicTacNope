// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "TicTacNopeGameState.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	//// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	Camera->bUsePawnControlRotation = true;


	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	Trigger->InitCapsuleSize(55.f, 96.0f);;
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForwardBack);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveLeftRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	// bind player action
	PlayerInputComponent->BindAction("PlayerAction", IE_Pressed, this, &APlayerCharacter::ClaimCell);
}

void APlayerCharacter::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ACell>())
	{
		ACell* cell = Cast<ACell>(OtherActor);
		
		if (cell->CurrentState == CellStates::Empty)
		{
			ClaimableCell = cell;
		}
	}
}

void APlayerCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ClaimableCell = NULL;
}


void APlayerCharacter::ClaimCell()
{
	if (ClaimableCell != NULL)
	{
		ClaimableCell->CurrentState = CellStates::PlayerOccupied;

		ATicTacNopeGameState* const gameState = GetWorld()->GetGameState<ATicTacNopeGameState>();
		gameState->CheckBoardCompletion(ClaimableCell);
	}
}


void APlayerCharacter::MoveForwardBack(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveLeftRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::TurnLeftRight(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpDown(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::PlayerTakeDamage()
{
	ATicTacNopeGameState* const gameState = GetWorld()->GetGameState<ATicTacNopeGameState>();
	gameState->UpdateBoardState(BoardStates::MonsterVictory);
}

void APlayerCharacter::Reset()
{
	UE_LOG(LogTemp, Error, TEXT("Reset Player"));

	//reset actor location
	SetActorLocation(StartingLocation);
}