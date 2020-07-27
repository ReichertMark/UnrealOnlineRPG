// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "MMOEngineSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API UMMOEngineSubSystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
  virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
