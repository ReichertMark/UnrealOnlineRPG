// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MMOCharacter.h"
#include "MMOAttributeSet.generated.h"


/**
 * This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
 * It would creates the following functions, for attribute Health
 *
 *	static FGameplayAttribute UMyHealthSet::GetHealthAttribute();
 *	FORCEINLINE float UMyHealthSet::GetHealth() const;
 *	FORCEINLINE void UMyHealthSet::SetHealth(float NewVal);
 *	FORCEINLINE void UMyHealthSet::InitHealth(float NewVal);
 *
 * To use this in your game you can define something like this, and then add game-specific functions as necessary:
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



/**
 * 
 */
UCLASS(EditInlineNew)
class MMO_API UMMOAttributeSet : public UAttributeSet
{
  GENERATED_UCLASS_BODY()

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internal")
  class AMMOCharacterAbilities* WhoAttackedUsLast;
	
public:

  // Health
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = RPGAttributes, meta = (HideFromModifiers))
  FGameplayAttributeData Health;
  UFUNCTION()
  void OnRep_Health() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Health); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Health)
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
  float MMOGetHealth() const
  {
    return Health.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
  void MMOSetHealth(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetHealthAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitHealth(float NewVal)
  {
    Health.SetBaseValue(NewVal);
    Health.SetCurrentValue(NewVal);
  }

  //MaxHealth
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category = RPGAttributes)
    FGameplayAttributeData MaxHealth;
  UFUNCTION()
    void OnRep_MaxHealth() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, MaxHealth); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, MaxHealth)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetMaxHealth() const
  {
    return MaxHealth.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetMaxHealth(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetMaxHealthAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitMaxHealth(float NewVal)
  {
    MaxHealth.SetBaseValue(NewVal);
    MaxHealth.SetCurrentValue(NewVal);
  }

  //HealthRegenRate
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HealthRegenRate, Category = RPGAttributes)
    FGameplayAttributeData HealthRegenRate;
  UFUNCTION()
    void OnRep_HealthRegenRate() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, HealthRegenRate); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, HealthRegenRate)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetHealthRegenRate() const
  {
    return HealthRegenRate.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetHealthRegenRate(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetHealthRegenRateAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitHealthRegenRate(float NewVal)
  {
    HealthRegenRate.SetBaseValue(NewVal);
    HealthRegenRate.SetCurrentValue(NewVal);
  }

  //Mana
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Mana, Category = RPGAttributes)
    FGameplayAttributeData Mana;
  UFUNCTION()
    void OnRep_Mana() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Mana); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Mana)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetMana() const
  {
    return Mana.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetMana(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetManaAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitMana(float NewVal)
  {
    Mana.SetBaseValue(NewVal);
    Mana.SetCurrentValue(NewVal);
  }

  //MaxMana
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxMana, Category = RPGAttributes)
    FGameplayAttributeData MaxMana;
  UFUNCTION()
    void OnRep_MaxMana() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, MaxMana); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, MaxMana)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetMaxMana() const
  {
    return MaxMana.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetMaxMana(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetMaxManaAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitMaxMana(float NewVal)
  {
    MaxMana.SetBaseValue(NewVal);
    MaxMana.SetCurrentValue(NewVal);
  }

  //ManaRegenRate
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ManaRegenRate, Category = RPGAttributes)
    FGameplayAttributeData ManaRegenRate;
  UFUNCTION()
    void OnRep_ManaRegenRate() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, ManaRegenRate); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, ManaRegenRate)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetManaRegenRate() const
  {
    return ManaRegenRate.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetManaRegenRate(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetManaRegenRateAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitManaRegenRate(float NewVal)
  {
    ManaRegenRate.SetBaseValue(NewVal);
    ManaRegenRate.SetCurrentValue(NewVal);
  }


  //Endurance
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Endurance, Category = RPGAttributes)
    FGameplayAttributeData Endurance;
  UFUNCTION()
    void OnRep_Endurance() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Endurance); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Endurance)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetEndurance() const
  {
    return Endurance.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetEndurance(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetEnduranceAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitEndurance(float NewVal)
  {
    Endurance.SetBaseValue(NewVal);
    Endurance.SetCurrentValue(NewVal);
  }

  //MaxEndurance
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxEndurance, Category = RPGAttributes)
    FGameplayAttributeData MaxEndurance;
  UFUNCTION()
    void OnRep_MaxEndurance() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, MaxEndurance); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, MaxEndurance)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetMaxEndurance() const
  {
    return MaxEndurance.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetMaxEndurance(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetMaxEnduranceAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitMaxEndurance(float NewVal)
  {
    MaxEndurance.SetBaseValue(NewVal);
    MaxEndurance.SetCurrentValue(NewVal);
  }

  //EnduranceRegenRate
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_EnduranceRegenRate, Category = RPGAttributes)
    FGameplayAttributeData EnduranceRegenRate;
  UFUNCTION()
    void OnRep_EnduranceRegenRate() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, EnduranceRegenRate); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, EnduranceRegenRate)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetEnduranceRegenRate() const
  {
    return EnduranceRegenRate.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetEnduranceRegenRate(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetEnduranceRegenRateAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitEnduranceRegenRate(float NewVal)
  {
    EnduranceRegenRate.SetBaseValue(NewVal);
    EnduranceRegenRate.SetCurrentValue(NewVal);
  }


  //Strength
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Strength, Category = RPGAttributes)
    FGameplayAttributeData Strength;
  UFUNCTION()
    void OnRep_Strength() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Strength); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Strength)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetStrength() const
  {
    return Strength.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetStrength(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetStrengthAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitStrength(float NewVal)
  {
    Strength.SetBaseValue(NewVal);
    Strength.SetCurrentValue(NewVal);
  }

  //Dexterity
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Dexterity, Category = RPGAttributes)
    FGameplayAttributeData Dexterity;
  UFUNCTION()
    void OnRep_Dexterity() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Dexterity); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Dexterity)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetDexterity() const
  {
    return Dexterity.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetDexterity(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetDexterityAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitDexterity(float NewVal)
  {
    Dexterity.SetBaseValue(NewVal);
    Dexterity.SetCurrentValue(NewVal);
  }

  //Constitution
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Constitution, Category = RPGAttributes)
    FGameplayAttributeData Constitution;
  UFUNCTION()
    void OnRep_Constitution() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Constitution); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Constitution)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetConstitution() const
  {
    return Constitution.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetConstitution(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetConstitutionAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitConstitution(float NewVal)
  {
    Constitution.SetBaseValue(NewVal);
    Constitution.SetCurrentValue(NewVal);
  }

  //Quickness
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Quickness, Category = RPGAttributes)
    FGameplayAttributeData Quickness;
  UFUNCTION()
    void OnRep_Quickness() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Quickness); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Quickness)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetQuickness() const
  {
    return Quickness.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetQuickness(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetQuicknessAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitQuickness(float NewVal)
  {
    Quickness.SetBaseValue(NewVal);
    Quickness.SetCurrentValue(NewVal);
  }

  //Charisma
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Intelligence, Category = RPGAttributes)
    FGameplayAttributeData Intelligence;
  UFUNCTION()
    void OnRep_Intelligence() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Intelligence); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Intelligence)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetIntelligence() const
  {
    return Intelligence.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetIntelligence(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetIntelligenceAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitIntelligence(float NewVal)
  {
    Intelligence.SetBaseValue(NewVal);
    Intelligence.SetCurrentValue(NewVal);
  }

  //Piety
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Piety, Category = RPGAttributes)
    FGameplayAttributeData Piety;
  UFUNCTION()
    void OnRep_Piety() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Piety); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Piety)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetPiety() const
  {
    return Piety.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetPiety(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetPietyAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitPiety(float NewVal)
  {
    Piety.SetBaseValue(NewVal);
    Piety.SetCurrentValue(NewVal);
  }

  //Empathy
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Empathy, Category = RPGAttributes)
    FGameplayAttributeData Empathy;
  UFUNCTION()
    void OnRep_Empathy() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Empathy); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Empathy)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetEmpathy() const
  {
    return Empathy.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetEmpathy(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetEmpathyAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitEmpathy(float NewVal)
  {
    Empathy.SetBaseValue(NewVal);
    Empathy.SetCurrentValue(NewVal);
  }

  //Charisma
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Charisma, Category = RPGAttributes)
    FGameplayAttributeData Charisma;
  UFUNCTION()
    void OnRep_Charisma() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, Charisma); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, Charisma)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetCharisma() const
  {
    return Charisma.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetCharisma(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetCharismaAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitCharisma(float NewVal)
  {
    Charisma.SetBaseValue(NewVal);
    Charisma.SetCurrentValue(NewVal);
  }



  // ---- Resistances ----

  //CrushResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CrushResist, Category = RPGAttributes)
    FGameplayAttributeData CrushResist;
  UFUNCTION()
    void OnRep_CrushResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, CrushResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, CrushResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetCrushResist() const
  {
    return CrushResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetCrushResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetCrushResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitCrushResist(float NewVal)
  {
    CrushResist.SetBaseValue(NewVal);
    CrushResist.SetCurrentValue(NewVal);
  }

  //SlashResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_SlashResist, Category = RPGAttributes)
    FGameplayAttributeData SlashResist;
  UFUNCTION()
    void OnRep_SlashResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, SlashResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, SlashResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetSlashResist() const
  {
    return SlashResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetSlashResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetSlashResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitSlashResist(float NewVal)
  {
    SlashResist.SetBaseValue(NewVal);
    SlashResist.SetCurrentValue(NewVal);
  }

  //ThrustResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ThrustResist, Category = RPGAttributes)
    FGameplayAttributeData ThrustResist;
  UFUNCTION()
    void OnRep_ThrustResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, ThrustResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, ThrustResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetThrustResist() const
  {
    return ThrustResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetThrustResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetThrustResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitThrustResist(float NewVal)
  {
    ThrustResist.SetBaseValue(NewVal);
    ThrustResist.SetCurrentValue(NewVal);
  }

  //HeatResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HeatResist, Category = RPGAttributes)
    FGameplayAttributeData HeatResist;
  UFUNCTION()
    void OnRep_HeatResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, HeatResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, HeatResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetHeatResist() const
  {
    return HeatResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetHeatResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetHeatResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitHeatResist(float NewVal)
  {
    HeatResist.SetBaseValue(NewVal);
    HeatResist.SetCurrentValue(NewVal);
  }

  //ColdResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ColdResist, Category = RPGAttributes)
    FGameplayAttributeData ColdResist;
  UFUNCTION()
    void OnRep_ColdResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, ColdResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, ColdResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetColdResist() const
  {
    return ColdResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetColdResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetColdResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitColdResist(float NewVal)
  {
    ColdResist.SetBaseValue(NewVal);
    ColdResist.SetCurrentValue(NewVal);
  }

  //MatterResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MatterResist, Category = RPGAttributes)
    FGameplayAttributeData MatterResist;
  UFUNCTION()
    void OnRep_MatterResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, MatterResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, MatterResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetMatterResist() const
  {
    return MatterResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetMatterResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetMatterResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitMatterResist(float NewVal)
  {
    MatterResist.SetBaseValue(NewVal);
    MatterResist.SetCurrentValue(NewVal);
  }

  // BodyResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_BodyResist, Category = RPGAttributes)
    FGameplayAttributeData BodyResist;
  UFUNCTION()
    void OnRep_BodyResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, BodyResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, BodyResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetBodyResist() const
  {
    return BodyResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetBodyResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetBodyResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitBodyResist(float NewVal)
  {
    BodyResist.SetBaseValue(NewVal);
    BodyResist.SetCurrentValue(NewVal);
  }

  //SpiritResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_SpiritResist, Category = RPGAttributes)
    FGameplayAttributeData SpiritResist;
  UFUNCTION()
    void OnRep_SpiritResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, SpiritResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, SpiritResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetSpiritResist() const
  {
    return SpiritResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetSpiritResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetSpiritResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitSpiritResist(float NewVal)
  {
    SpiritResist.SetBaseValue(NewVal);
    SpiritResist.SetCurrentValue(NewVal);
  }

  //EnergyResist
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_EnergyResist, Category = RPGAttributes)
    FGameplayAttributeData EnergyResist;
  UFUNCTION()
    void OnRep_EnergyResist() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, EnergyResist); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, EnergyResist)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetEnergyResist() const
  {
    return EnergyResist.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetEnergyResist(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetEnergyResistAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitEnergyResist(float NewVal)
  {
    EnergyResist.SetBaseValue(NewVal);
    EnergyResist.SetCurrentValue(NewVal);
  }

  //ArmorFactor
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ArmorFactor, Category = RPGAttributes)
    FGameplayAttributeData ArmorFactor;
  UFUNCTION()
    void OnRep_ArmorFactor() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, ArmorFactor); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, ArmorFactor)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetArmorFactor() const
  {
    return ArmorFactor.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetArmorFactor(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetArmorFactorAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitArmorFactor(float NewVal)
  {
    ArmorFactor.SetBaseValue(NewVal);
    ArmorFactor.SetCurrentValue(NewVal);
  }

  //DamagePerSecond
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_DamagePerSecond, Category = RPGAttributes)
    FGameplayAttributeData DamagePerSecond;
  UFUNCTION()
    void OnRep_DamagePerSecond() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, DamagePerSecond); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, DamagePerSecond)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetDamagePerSecond() const
  {
    return DamagePerSecond.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetDamagePerSecond(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetDamagePerSecondAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitDamagePerSecond(float NewVal)
  {
    DamagePerSecond.SetBaseValue(NewVal);
    DamagePerSecond.SetCurrentValue(NewVal);
  }

  //ArmorAbsorption
  UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ArmorAbsorption, Category = RPGAttributes)
    FGameplayAttributeData ArmorAbsorption;
  UFUNCTION()
    void OnRep_ArmorAbsorption() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSet, ArmorAbsorption); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSet, ArmorAbsorption)
    UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    float MMOGetArmorAbsorption() const
  {
    return ArmorAbsorption.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOSetArmorAbsorption(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetArmorAbsorptionAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = RPGAttributes)
    void MMOInitArmorAbsorption(float NewVal)
  {
    ArmorAbsorption.SetBaseValue(NewVal);
    ArmorAbsorption.SetCurrentValue(NewVal);
  }



  /** This Damage is just used for applying negative health mods. Its not a 'persistent' attribute. */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromLevelInfos))		// You can't make a GameplayEffect 'powered' by Damage (Its transient)
  FGameplayAttributeData	Damage;

  /** This Healing is just used for applying positive health mods. Its not a 'persistent' attribute. */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromLevelInfos))		// You can't make a GameplayEffect 'powered' by Healing (Its transient)
  FGameplayAttributeData	Healing;

  virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
  virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
