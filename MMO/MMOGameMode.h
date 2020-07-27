// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MMOGameMode.generated.h"

UCLASS()
class AMMOGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMMOGameMode();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    FVector DebugStartLocation;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    FString DebugCharacterName;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float SaveIntervalInSeconds;

  //Time of Day
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeOfDay")
    float LocalSecondsOffset; //The time offset when this instance started

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeOfDay")
    float DayLengthInSeconds;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeOfDay")
    float DaysPerLunarCycle;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeOfDay")
    float DaysPerSolarCycle;

  //Get Current World Time
  //Lookup a zone instance from a given port
  UFUNCTION(BlueprintCallable, Category = "Zones")
    void GetCurrentWorldTime();

  UFUNCTION(BlueprintImplementableEvent, Category = "Zones")
    void NotifyGetCurrentWorldTime(const float CurrentWorldTime);


  virtual void StartPlay();

  APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, class AActor* StartSpot);

protected:

  FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal);

};



