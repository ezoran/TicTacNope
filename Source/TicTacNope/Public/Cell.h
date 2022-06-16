// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacNopeTypes.h"
#include "Components/BoxComponent.h"
#include "Cell.generated.h"


UCLASS()
class TICTACNOPE_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CellId;

	/* track the current state of the cell*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CellStates CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TriggerExtents = FVector(128, 128, 128);
	
	void ModifyState(CellStates updatedState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UBoxComponent* BoxComponent;

};