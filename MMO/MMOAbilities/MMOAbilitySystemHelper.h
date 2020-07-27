// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "MMO/MMOGlobalConstants.h"
#include "MMOAbilitySystemHelper.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API UMMOAbilitySystemHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
  // --- Abilities ---

  // Gets the cool down effect class of the specified gameplay ability class. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static TSubclassOf<UGameplayEffect> GetCooldownEffect(TSubclassOf<UGameplayAbility> Ability);

  // Gets the remaining cool down time. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static float GetCooldownTimeRemaining(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability, bool WarnIfSetByCallFail);

  // Gets the cool down duration. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static float GetCooldownTimeDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability, bool WarnIfSetByCallFail);

  // Gets the cool down time and duration. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static void GetCooldownTimeRemainingAndDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability, float& OutRemainingCooldownTime, float& OutCooldownDuration, bool WarnIfSetByCallFail);

  // Gets the icon of the specified gameplay ability class. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static UTexture2D* GetAbilityIcon(TSubclassOf<UGameplayAbility> Ability);

  // Gets the current level of an ability. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static int32 GetAbilityLevel(TSubclassOf<UGameplayAbility> Ability);

  // Gets the name of the ability. Can be shown in the UI. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static FText GetAbilityName(TSubclassOf<UGameplayAbility> Ability);

  // Gets the name of the ability. Can be shown in the UI. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static FText GetAbilityDescription(TSubclassOf<UGameplayAbility> Ability);

  // Gets the target type of the specified gameplay ability class.
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static ETargetType GetAbilityTargetType(TSubclassOf<UGameplayAbility> Ability);

  // Gets the type of the specified gameplay ability class. (Spell or Skill, Common, etc)
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static EAbilityType GetAbilityType(TSubclassOf<UGameplayAbility> Ability);

  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static float GetAbilityCooldownDuration(TSubclassOf<UGameplayAbility> Ability);

  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static float GetAbilityCastTime(TSubclassOf<UGameplayAbility> Ability);

  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure)
  static float GetAbilityDamage(TSubclassOf<UGameplayAbility> Ability);

  // Cancels the ability of the specified type. 
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintCallable)
  static void CancelAbility(UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability);

  // Whether the specified ability is currently active. Returns always false for clients.  
  UFUNCTION(Category = "MMO Ability|Abilities", BlueprintPure, meta = (DisplayName = "IsAbilityActive (Server only)"))
  static bool IsAbilityActive(UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayAbility> Ability);


  // --- Effects ---


  // Gets the remaining time of the specified effect.  Returns 0 if the effect is not active on this ability system.
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static float GetActiveEffectTimeRemaining(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayEffect> Effect);

  // Gets the duration of the gameplay effect that is currently active on the ability system component. Returns 0 if the effect is not active on this ability system.
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static float GetActiveEffectDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayEffect> Effect);

  // Gets the cool down time and duration.
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static void GetActiveEffectTimeRemainingAndDuration(const UAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayEffect> Effect, float& OutRemainingTime, float& OutDuration);

  // Returns the list of all gameplay effects that are currently active for the given ability system component. 
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static TArray<TSubclassOf<UGameplayEffect>> GetActiveGameplayEffects(const UAbilitySystemComponent* AbilitySystem);

  //Returns the list of all gameplay effects that are currently active for the given ability system component, along with additional data such as duration and stacks.
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static TArray<FGameplayEffectSpec> GetActiveGameplayEffectSpecs(const UAbilitySystemComponent* AbilitySystem);

  // Returns the gameplay effect class of the specified gameplay effect spec.
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static TSubclassOf<UGameplayEffect> GetGameplayEffectSpecClass(const FGameplayEffectSpec& GameplayEffectSpec);

  // Returns the number of stacks of the specified gameplay effect spec. 
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static int32 GetGameplayEffectSpecStackCount(const FGameplayEffectSpec& GameplayEffectSpec);

  // Gets the icon of the specified gameplay effect class. 
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static UTexture2D* GetEffectIcon(TSubclassOf<UGameplayEffect> Effect);

  // Gets the name of the specified gameplay effect class. 
  UFUNCTION(Category = "MMO Ability|Effects", BlueprintPure)
  static FText GetEffectName(TSubclassOf<UGameplayEffect> Effect);

  // Gets the description of the specified gameplay effect class. 
  UFUNCTION(Category = "RTS Ability|Effects", BlueprintPure)
  static FText GetEffectDescription(TSubclassOf<UGameplayEffect> Effect);

};
