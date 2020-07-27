// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMOCharacterAbilities.h"
#include "MMOPlayerCharacterAbilities.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API AMMOPlayerCharacterAbilities : public AMMOCharacterAbilities
{
	GENERATED_BODY()
	

public:
  virtual void Die(AMMOCharacterAbilities* Killer);

};
