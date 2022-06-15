// Fill out your copyright notice in the Description page of Project Settings.
#include "Cell.h"
#include "GameFramework/Actor.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CellTrigger"));
	BoxComponent->InitBoxExtent(TriggerExtents);

	BoxComponent->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	//BoxComponent->SetGenerateOverlapEvents(true);
//	BoxComponent->AttachToComponent(RootComponent);

}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();

//	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACell::OnBeginOverlap);
	
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACell::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("OnBeginOverlap Called"));
	//UE_LOG(LogTemp, Warning, TEXT("Yo you gots a collision bruh"));
}

void ACell::ModifyState(CellStates updatedState)
{
	CurrentState = updatedState;
}