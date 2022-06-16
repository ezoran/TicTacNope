// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Cell.h"
//#include "MonsterAIController.h"
#include "PlayerCharacter.h"
#include "TicTacNopeGameState.h"
#include "GameFramework/Character.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class TICTACNOPE_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterCharacter();

	UMonsterAnimInstance* AnimInstance;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void UpdateMonsterState(MonsterStates UpdatedState);

	/* modified both here and from the AI Controller to manage the monster's state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	MonsterStates CurrentState;

	/* speed at which monster moves towards cells*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkingSpeed;

	/* speed at which monster chase the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunningSpeed;

private:

	UFUNCTION()
	void HandleClaimingCell(ACell* Cell);

	UFUNCTION()
	void HandleAttacking(APlayerCharacter* Player);

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UCapsuleComponent* Trigger;

};
