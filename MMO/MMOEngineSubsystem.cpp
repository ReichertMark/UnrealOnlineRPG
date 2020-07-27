// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOEngineSubSystem.h"
#include "AbilitySystemGlobals.h"

void UMMOEngineSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
  Super::Initialize(Collection);

  UAbilitySystemGlobals::Get().InitGlobalData();


  UE_LOG(LogTemp, Warning, TEXT("UMMOEngineSubSystem::Initialize"));
}