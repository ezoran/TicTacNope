// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Cell.h"
#include "TicTacNopeTypes.h"
#include "PlayerCharacter.generated.h"


class UInputComponent;
class USceneComponent;
class UCameraComponent;
class USoundBase;

UCLASS()
class TICTACNOPE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		

public:

	APlayerCharacter();

	/* Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;


protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Forward Backword movement */
	void MoveForwardBack(float Val);

	/* Left and right movement */
	void MoveLeftRight(float Val);
	
	/* Look left and right */
	void TurnLeftRight(float Rate);

	/* Look up and down */
	void LookUpDown(float Rate);

	void ClaimCell();

public:	

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return Camera; }

	UFUNCTION()
	void PlayerTakeDamage();

	UFUNCTION()
	void Reset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartingLocation;

private: 

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);	
	
	UCapsuleComponent* Trigger;

	ACell* ClaimableCell;
};
