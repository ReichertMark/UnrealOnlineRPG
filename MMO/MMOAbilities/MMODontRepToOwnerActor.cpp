// Fill out your copyright notice in the Description page of Project Settings.


#include "MMODontRepToOwnerActor.h"

// Sets default values
AMMODontRepToOwnerActor::AMMODontRepToOwnerActor()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  bReplicates = true;
  bReplicateMovement = true;
  bNetUseOwnerRelevancy = false;
  bOnlyRelevantToOwner = false;
}

// Called when the game starts or when spawned
void AMMODontRepToOwnerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMMODontRepToOwnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMMODontRepToOwnerActor::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
  return !IsOwnedBy(ViewTarget);
}

