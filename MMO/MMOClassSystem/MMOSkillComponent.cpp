// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOSkillComponent.h"

// Sets default values for this component's properties
UMMOSkillComponent::UMMOSkillComponent()
{
  AttributeSetSkills = CreateDefaultSubobject<UMMOAttributeSetSkills>(TEXT("AttributeSetSkills"));
}


// Called when the game starts
void UMMOSkillComponent::BeginPlay()
{
	Super::BeginPlay();

  // server only
  if (GetOwnerRole() == ROLE_Authority)
  {
  }
}

