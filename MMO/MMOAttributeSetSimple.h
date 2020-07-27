// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/ObjectMacros.h"
#include "AbilitySystemComponent.h"
#include "MMOAttributeSetSimple.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API UMMOAttributeSetSimple : public UAttributeSet
{
  GENERATED_UCLASS_BODY()
	

public:

  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category = "SimpleAttributes")//, meta = (HideFromModifiers))			// You can't make a GameplayEffect modify Health Directly (go through)
    mutable float	MaxHealth;
  UFUNCTION()
    void OnRep_MaxHealth()
  {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSetSimple, MaxHealth);
  }

  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "SimpleAttributes", meta = (HideFromModifiers))
    mutable float	Health;
  UFUNCTION()
    void OnRep_Health() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSetSimple, Health); }

  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HealthRegenRate, Category = "SimpleAttributes")
    mutable float HealthRegenRate;
  UFUNCTION()
    void OnRep_HealthRegenRate() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSetSimple, HealthRegenRate); }

  /** This Damage is just used for applying negative health mods. Its not a 'persistent' attribute. */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromLevelInfos))		// You can't make a GameplayEffect 'powered' by Damage (Its transient)
    mutable float	Damage;

  /** This Healing is just used for applying positive health mods. Its not a 'persistent' attribute. */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromLevelInfos))		// You can't make a GameplayEffect 'powered' by Healing (Its transient)
    mutable float	Healing;

  virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
  virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
