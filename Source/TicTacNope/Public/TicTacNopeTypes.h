// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class CellStates : uint8
{
	Empty,
	PlayerOccupied,
	MonsterOccupied
};

UENUM(BlueprintType)
enum class MonsterStates : uint8
{
	Idle,
	WalkTowardsCell,
	FillingCell,
	ChasePlayer,
	AttackingPlayer
};

UENUM(BlueprintType)
enum class BoardStates : uint8
{
	Inactive,
	InProgress,
	PlayerVictory,
	MonsterVictory,
	PlayerMonsterDraw
};