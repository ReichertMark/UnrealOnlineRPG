// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOAbilitySystemHelper.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "GameplayAbilitySpec.h"
#include "GameplayCueManager.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SCS_Node.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "MMO/MMOAbilities/MMOGameplayAbility.h"
#include "MMO/MMOAbilities/MMOGameplayEffect.h"

TSubclassOf<UGameplayEffect> UMMOAbilitySystemHelper::GetCooldownEffect(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return nullptr;
  }

  UGameplayEffect* CooldownEffect = Ability->GetDefaultObject<UGameplayAbility>()->GetCooldownGameplayEffect();
  return CooldownEffect != nullptr ? CooldownEffect->GetClass() : nullptr;
}


float UMMOAbilitySystemHelper::GetCooldownTimeRemaining(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability, bool WarnIfSetByCallFail)
{
  float Time;
  float Duration;
  GetCooldownTimeRemainingAndDuration(AbilitySystem, Ability, Time, Duration, WarnIfSetByCallFail);
  return Time;
}

float UMMOAbilitySystemHelper::GetCooldownTimeDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability, bool WarnIfSetByCallFail)
{
  float Time;
  float Duration;
  GetCooldownTimeRemainingAndDuration(AbilitySystem, Ability, Time, Duration, WarnIfSetByCallFail);
  return Duration;
}

void UMMOAbilitySystemHelper::GetCooldownTimeRemainingAndDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability, float& OutRemainingCooldownTime, float& OutCooldownDuration, bool WarnIfSetByCallFail)
{
  TSubclassOf<UGameplayEffect> CooldownEffectClass = GetCooldownEffect(Ability);

  GetActiveEffectTimeRemainingAndDuration(AbilitySystem, CooldownEffectClass, OutRemainingCooldownTime,
    OutCooldownDuration);

  if (CooldownEffectClass && OutCooldownDuration == 0)
  {
    // If we didn't find any cooldown duration, it might be due to the fact that no cooldown effect is active. Try
    // using the CDO.
    const UGameplayEffect* CooldownEffect = CooldownEffectClass->GetDefaultObject<UGameplayEffect>();
    FGameplayEffectSpec CooldownEffectSpec(CooldownEffect, FGameplayEffectContextHandle());
    CooldownEffect->DurationMagnitude.AttemptCalculateMagnitude(CooldownEffectSpec, OutCooldownDuration, WarnIfSetByCallFail);
  }
}

UTexture2D* UMMOAbilitySystemHelper::GetAbilityIcon(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return nullptr;
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  return GameplayAbility != nullptr ? GameplayAbility->GetIcon() : nullptr;
}

int32 UMMOAbilitySystemHelper::GetAbilityLevel(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return 0;
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  return GameplayAbility != nullptr ? GameplayAbility->GetLevel() : 0;
}

FText UMMOAbilitySystemHelper::GetAbilityName(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return FText::FromString(TEXT("MMOAbilitySystemHelper::GetAbilityName: Error: Parameter 'Ability' was 'nullptr'."));
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  if (GameplayAbility == nullptr)
  {
    return FText::FromString(TEXT("MMOAbilitySystemHelper::GetAbilityName: Error: Parameter 'Ability' was not a 'MMOGameplayAbility'."));
  }

  return GameplayAbility->GetName();
}

FText UMMOAbilitySystemHelper::GetAbilityDescription(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return FText::FromString(TEXT("MMOAbilitySystemHelper::GetAbilityName: Error: Parameter 'Ability' was 'nullptr'."));
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  if (GameplayAbility == nullptr)
  {
    return FText::FromString(TEXT("MMOAbilitySystemHelper::GetAbilityDescription: Error: Parameter 'Ability' was not a 'MMOGameplayAbility'."));
  }

  return GameplayAbility->GetDescription();
}

ETargetType UMMOAbilitySystemHelper::GetAbilityTargetType(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return ETargetType::Self;
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  return GameplayAbility != nullptr ? GameplayAbility->GetTargetType() : ETargetType::Self;
}

EAbilityType UMMOAbilitySystemHelper::GetAbilityType(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return EAbilityType::Common;
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  return GameplayAbility != nullptr ? GameplayAbility->GetAbilityType() : EAbilityType::Common;
}

float UMMOAbilitySystemHelper::GetAbilityCooldownDuration(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return 0.0F;
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  return GameplayAbility != nullptr ? GameplayAbility->GetCooldownDuration() : 0.0F;
}

float UMMOAbilitySystemHelper::GetAbilityCastTime(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return 0.0F;
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  return GameplayAbility != nullptr ? GameplayAbility->GetCastTime() : 0.0F;
}

float UMMOAbilitySystemHelper::GetAbilityDamage(TSubclassOf<UGameplayAbility> Ability)
{
  if (Ability == nullptr)
  {
    return 0.0F;
  }

  UMMOGameplayAbility* GameplayAbility = Cast<UMMOGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
  return GameplayAbility != nullptr ? GameplayAbility->GetDamage() : 0.0F;
}

void UMMOAbilitySystemHelper::CancelAbility(UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability)
{
  if (AbilitySystem == nullptr || Ability == nullptr)
  {
    return;
  }

  AbilitySystem->CancelAbility(Ability->GetDefaultObject<UGameplayAbility>());
}

bool UMMOAbilitySystemHelper::IsAbilityActive(UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability)
{
  if (AbilitySystem == nullptr || Ability == nullptr)
  {
    return false;
  }

  FGameplayAbilitySpec* Spec = AbilitySystem->FindAbilitySpecFromClass(Ability);

  return Spec->IsActive();
}

// --- Effects ---

float UMMOAbilitySystemHelper::GetActiveEffectTimeRemaining(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayEffect> Effect)
{
  float Time;
  float Duration;
  GetActiveEffectTimeRemainingAndDuration(AbilitySystem, Effect, Time, Duration);
  return Time;
}

float UMMOAbilitySystemHelper::GetActiveEffectDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayEffect> Effect)
{
  float Time;
  float Duration;
  GetActiveEffectTimeRemainingAndDuration(AbilitySystem, Effect, Time, Duration);
  return Duration;
}

void UMMOAbilitySystemHelper::GetActiveEffectTimeRemainingAndDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayEffect> Effect, float& OutRemainingTime, float& OutDuration)
{
  // Make sure to always assign out references
  OutRemainingTime = 0.0f;
  OutDuration = 0.0f;

  if (Effect != nullptr && AbilitySystem != nullptr)
  {
    FGameplayEffectQuery Query;
    Query.EffectDefinition = Effect;
    TArray<TPair<float, float>> RemainingTimes = AbilitySystem->GetActiveEffectsTimeRemainingAndDuration(Query);

    for (int32 i = 0; i < RemainingTimes.Num(); ++i)
    {
      TPair<float, float> Pair = RemainingTimes[i];
      float Time = Pair.Key;
      float Duration = Pair.Value;

      if (Time > OutRemainingTime)
      {
        OutRemainingTime = Time;
      }

      if (Duration > OutDuration)
      {
        OutDuration = Duration;
      }
    }
  }
}


TArray<TSubclassOf<UGameplayEffect>> UMMOAbilitySystemHelper::GetActiveGameplayEffects(const UAbilitySystemComponent* AbilitySystem)
{
  TArray<TSubclassOf<UGameplayEffect>> OutEffects;
  if (AbilitySystem == nullptr)
  {
    return OutEffects;
  }

  TArray<FGameplayEffectSpec> OutEffectSpecs;
  AbilitySystem->GetAllActiveGameplayEffectSpecs(OutEffectSpecs);

  for (const FGameplayEffectSpec& EffectSpec : OutEffectSpecs)
  {
    OutEffects.Add(EffectSpec.Def->GetClass());
  }

  return OutEffects;
}

TArray<FGameplayEffectSpec> UMMOAbilitySystemHelper::GetActiveGameplayEffectSpecs(const UAbilitySystemComponent* AbilitySystem)
{
  TArray<FGameplayEffectSpec> OutEffectSpecs;
  AbilitySystem->GetAllActiveGameplayEffectSpecs(OutEffectSpecs);
  return OutEffectSpecs;
}

TSubclassOf<UGameplayEffect> UMMOAbilitySystemHelper::GetGameplayEffectSpecClass(const FGameplayEffectSpec& GameplayEffectSpec)
{
  return GameplayEffectSpec.Def->GetClass();
}

int32 UMMOAbilitySystemHelper::GetGameplayEffectSpecStackCount(const FGameplayEffectSpec& GameplayEffectSpec)
{
  return GameplayEffectSpec.StackCount;
}

UTexture2D* UMMOAbilitySystemHelper::GetEffectIcon(TSubclassOf<UGameplayEffect> Effect)
{
  if (Effect == nullptr)
  {
    return nullptr;
  }

  UMMOGameplayEffect* GameplayEffect = Cast<UMMOGameplayEffect>(Effect->GetDefaultObject<UGameplayEffect>());
  return GameplayEffect != nullptr ? GameplayEffect->GetEffectIcon() : nullptr;
}

FText UMMOAbilitySystemHelper::GetEffectName(TSubclassOf<UGameplayEffect> Effect)
{
  if (Effect == nullptr)
  {
    return FText();
  }

  UMMOGameplayEffect* GameplayEffect = Cast<UMMOGameplayEffect>(Effect->GetDefaultObject<UGameplayEffect>());
  return GameplayEffect != nullptr ? GameplayEffect->GetEffectName() : FText();
}

FText UMMOAbilitySystemHelper::GetEffectDescription(TSubclassOf<UGameplayEffect> Effect)
{
  if (Effect == nullptr)
  {
    return FText();
  }

  UMMOGameplayEffect* GameplayEffect = Cast<UMMOGameplayEffect>(Effect->GetDefaultObject<UGameplayEffect>());
  return GameplayEffect != nullptr ? GameplayEffect->GetEffectDescription() : FText();
}