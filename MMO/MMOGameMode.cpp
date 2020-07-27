// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MMOGameMode.h"
#include "MMOCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <Engine/World.h>
#include "MMOPlayerState.h"

AMMOGameMode::AMMOGameMode()
{
 	// set default pawn class to our Blueprinted character
  // Blueprint'/Game/ThirdPersonCPP/Blueprints/PlayerCharacterWithAbilities.PlayerCharacterWithAbilities'
//  	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/PlayerCharacterWithAbilities"));
//  	if (PlayerPawnBPClass.Class != NULL)
//  	{
//  		DefaultPawnClass = PlayerPawnBPClass.Class;
//  	}
}

void AMMOGameMode::GetCurrentWorldTime()
{
  // TODO SERVER:

  static float fCurrentWorldTime = 0.0f;//9043294.0;
  fCurrentWorldTime += 1.0f;

  NotifyGetCurrentWorldTime(fCurrentWorldTime);

}

void AMMOGameMode::StartPlay()
{
  Super::StartPlay();

  UE_LOG(LogTemp, Warning, TEXT("AMMOGameMode::StartPlay"));
}

APawn* AMMOGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, class AActor* StartSpot)
{
  UE_LOG(LogTemp, Warning, TEXT("SpawnDefaultPawnFor_Implementation"));

  FActorSpawnParameters SpawnInfo;
  SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  SpawnInfo.Owner = this;
  SpawnInfo.Instigator = Instigator;
  SpawnInfo.ObjectFlags |= RF_Transient;

  SpawnInfo.bDeferConstruction = false;
  APawn* retPawn;

  AMMOPlayerState* NewPlayerState = CastChecked<AMMOPlayerState>(NewPlayer->PlayerState);
  UE_LOG(LogTemp, Warning, TEXT("Spawn Location is %f, %f, %f"), NewPlayerState->PlayerStartLocation.X, NewPlayerState->PlayerStartLocation.Y, NewPlayerState->PlayerStartLocation.Z);
  UE_LOG(LogTemp, Warning, TEXT("Spawn Rotation is %f, %f, %f"), NewPlayerState->PlayerStartRotation.Roll, NewPlayerState->PlayerStartRotation.Pitch, NewPlayerState->PlayerStartRotation.Yaw);

  retPawn = GetWorld()->SpawnActor<APawn>(GetDefaultPawnClassForController(NewPlayer), NewPlayerState->PlayerStartLocation, NewPlayerState->PlayerStartRotation, SpawnInfo);


  if (retPawn == NULL)
  {
    UE_LOG(LogTemp, Error, TEXT("Couldn't spawn Pawn in SpawnDefaultPawnFor_Implementation"));
  }

  return retPawn;
}

FString AMMOGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
  FString retString = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

  UE_LOG(LogTemp, Warning, TEXT("AMMOGameMode::InitNewPlayer"));

  UE_LOG(LogTemp, Warning, TEXT("Raw options: %s"), *Options);

  FString DecodedOptions = FGenericPlatformHttp::UrlDecode(Options);

  UE_LOG(LogTemp, Warning, TEXT("Decoded options: %s"), *DecodedOptions);

  FString PLX = UGameplayStatics::ParseOption(DecodedOptions, TEXT("PLX"));
  FString PLY = UGameplayStatics::ParseOption(DecodedOptions, TEXT("PLY"));
  FString PLZ = UGameplayStatics::ParseOption(DecodedOptions, TEXT("PLZ"));
  FString PRX = UGameplayStatics::ParseOption(DecodedOptions, TEXT("PRX"));
  FString PRY = UGameplayStatics::ParseOption(DecodedOptions, TEXT("PRY"));
  FString PRZ = UGameplayStatics::ParseOption(DecodedOptions, TEXT("PRZ"));
  FString PlayerName1 = UGameplayStatics::ParseOption(DecodedOptions, TEXT("Luri"));

  UE_LOG(LogTemp, Warning, TEXT("PlayerName: %s"), *PlayerName1);

  FString MMODefaultPawnClass = TEXT("/Game/MMO/Blueprints/PlayerCharacterWithAbilities");//UGameplayStatics::ParseOption(DecodedOptions, TEXT("DPC"));


  if (PlayerName1 == "")
  {
    PlayerName1 = DebugCharacterName;
  }

  float fPLX = FCString::Atof(*PLX);
  float fPLY = FCString::Atof(*PLY);
  float fPLZ = FCString::Atof(*PLZ);
  float fPRX = FCString::Atof(*PRX);
  float fPRY = FCString::Atof(*PRY);
  float fPRZ = FCString::Atof(*PRZ);

  UE_LOG(LogTemp, Warning, TEXT("Incoming start location is %f, %f, %f"), fPLX, fPLY, fPLZ);

  AMMOPlayerState* NewPlayerState = CastChecked<AMMOPlayerState>(NewPlayerController->PlayerState);



  if (fPLX != 0 || fPLY != 0 || fPLZ != 0)
  {
    NewPlayerState->PlayerStartLocation.X = fPLX;
    NewPlayerState->PlayerStartLocation.Y = fPLY;
    NewPlayerState->PlayerStartLocation.Z = fPLZ;
    NewPlayerState->PlayerStartRotation.Roll = fPRX;
    NewPlayerState->PlayerStartRotation.Pitch = fPRY;
    NewPlayerState->PlayerStartRotation.Yaw = fPRZ;
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Using Debug Start location"));
    NewPlayerState->PlayerStartLocation.X = DebugStartLocation.X;
    NewPlayerState->PlayerStartLocation.Y = DebugStartLocation.Y;
    NewPlayerState->PlayerStartLocation.Z = DebugStartLocation.Z;
    NewPlayerState->PlayerStartRotation.Roll = 0;
    NewPlayerState->PlayerStartRotation.Pitch = 0;
    NewPlayerState->PlayerStartRotation.Yaw = 0;
  }

  UE_LOG(LogTemp, Warning, TEXT("NewPlayerState->PlayerStartLocation is %f, %f, %f"), NewPlayerState->PlayerStartLocation.X, NewPlayerState->PlayerStartLocation.Y, NewPlayerState->PlayerStartLocation.Z);

  if (PlayerName1.IsEmpty())
  {
    PlayerName1 = DebugCharacterName;
    UE_LOG(LogTemp, Warning, TEXT("Using DebugCharacterName"));
  }

  NewPlayerState->SetPlayerName(PlayerName1);
  NewPlayerState->DefaultPawnClass = MMODefaultPawnClass;


  return retString;
}
