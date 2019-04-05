// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameplayGameMode.generated.h"

/**
 * 
 */

class UDataTable;

UCLASS()
class LOWPOLY_WORLD_API AGameplayGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UDataTable* GetItemDB() const { return ItemDB; }

protected:

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ItemDB;
};
