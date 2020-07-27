// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOGameplayAbility.h"

UTexture2D* UMMOGameplayAbility::GetIcon() const
{
  return Icon;
}

FText UMMOGameplayAbility::GetName() const
{
  return Name;
}

int32 UMMOGameplayAbility::GetLevel() const
{
  return Level;
}

EAbilityType UMMOGameplayAbility::GetAbilityType() const
{
  return AbilityType;
}


ETargetType UMMOGameplayAbility::GetTargetType() const
{
  return TargetType;
}

FText UMMOGameplayAbility::GetDescription() const
{
  return Description;
}

float UMMOGameplayAbility::GetCooldownDuration() const
{
  return Duration;
}

float UMMOGameplayAbility::GetCastTime() const
{
  return CastTime;
}

float UMMOGameplayAbility::GetDamage() const
{
  return Damage;
}
