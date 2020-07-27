// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MMO/MMOGlobalConstants.h"
#include "MMOGameplayAbility.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract, Blueprintable)
class MMO_API UMMOGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:
  UFUNCTION(Category = MMOAbility, BlueprintPure)
  UTexture2D* GetIcon() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  FText GetName() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  int32 GetLevel() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  EAbilityType GetAbilityType() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  ETargetType GetTargetType() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  FText GetDescription() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  float GetCooldownDuration() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  float GetCastTime() const;

  UFUNCTION(Category = MMOAbility, BlueprintPure)
  float GetDamage() const;



protected:
  UPROPERTY(Category = "MMOAbility", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  FText Name;

  UPROPERTY(Category = "MMOAbility", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  int32 Level;

  UPROPERTY(Category = "MMOAbility", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  EAbilityType AbilityType;

  UPROPERTY(Category = "MMOAbility", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  UTexture2D* Icon = nullptr;

  UPROPERTY(Category = "MMOAbility", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  ETargetType TargetType;

  UPROPERTY(Category = "MMOAbility", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  FText Description;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float Range;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float ManaCost;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float CastTime;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float Damage;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  EDamageType DamageType;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  ESpellType SpellType;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float Duration;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float Frequency;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float Pulse;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float PulseMana;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float Radius;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float CoolDown;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float ResurrectHealth;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float ResurrectMana;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float Concentration;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  float LifeDrainReturn;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  bool CanMoveWhileCasting;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  bool IsUninterruptable;

  UPROPERTY(Category = "Spell", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  bool IsFocus;

};
