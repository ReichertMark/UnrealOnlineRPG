// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOPlayerState.h"

void AMMOPlayerState::SetCharacterName(FString CharacterName)
{
  SetPlayerName(CharacterName);
}

AMMOCharacter* AMMOPlayerState::GetCurrentPawn()
{
  return Cast<AMMOCharacter>(GetPawn());
}