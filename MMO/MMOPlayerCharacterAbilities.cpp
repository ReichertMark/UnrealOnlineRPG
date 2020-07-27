// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOPlayerCharacterAbilities.h"

void AMMOPlayerCharacterAbilities::Die(AMMOCharacterAbilities* Killer)
{
  Super::Die(Killer);

  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOPlayerCharacterAbilities: Die called on client "));
    return;
  }

  UE_LOG(LogTemp, Warning, TEXT("AMMOPlayerCharacterAbilities: %s was killed by: %s "), *GetName(), *Killer->GetName());
}
