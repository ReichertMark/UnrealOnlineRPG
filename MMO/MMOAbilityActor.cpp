// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOAbilityActor.h"

AMMOAbilityActor::AMMOAbilityActor()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  bReplicates = true;

  AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
  AbilitySystem->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AMMOAbilityActor::BeginPlay()
{
  Super::BeginPlay();

  MMOAttributesSimple = NewObject<UMMOAttributeSetSimple>();

  if (AbilitySystem)
  {
    AbilitySystem->InitAbilityActorInfo(this, this);
  }
}

void AMMOAbilityActor::PostInitializeComponents()
{
  Super::PostInitializeComponents();

  if (AbilitySystem)
  {
    AbilitySystem->InitStats(UMMOAttributeSetSimple::StaticClass(), NULL);
  }
}

// Called every frame
void AMMOAbilityActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

