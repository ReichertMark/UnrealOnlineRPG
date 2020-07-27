// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOGameplayEffect.h"

UTexture2D* UMMOGameplayEffect::GetEffectIcon() const
{
  return EffectIcon;
}

FText UMMOGameplayEffect::GetEffectName() const
{
  return !EffectName.IsEmpty() ? EffectName : FText::FromString(GetClass()->GetName());
}

FText UMMOGameplayEffect::GetEffectDescription() const
{
  return EffectDescription;
}