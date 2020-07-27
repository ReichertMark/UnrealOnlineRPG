// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOAttributeSetSkills.h"
#include "Net/UnrealNetwork.h"


UMMOAttributeSetSkills::UMMOAttributeSetSkills(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
  TwoHanded = 0.0f;
}

void UMMOAttributeSetSkills::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  // Health, Mana and Endurance
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSetSkills, TwoHanded, COND_None, REPNOTIFY_Always);

}
