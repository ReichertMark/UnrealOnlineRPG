// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"
#include "GameplayTagsModule.h"
#include "GameplayEffectExtension.h"
#include "MMOCharacterAbilities.h"

UMMOAttributeSet::UMMOAttributeSet(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
  Health = 80.f;
  MaxHealth = 100.f;
  HealthRegenRate = 1.0f;

  Mana = 70.f;
  MaxMana = 100.f;
  ManaRegenRate = 0.3f;//0.3f;

  Endurance = 70.f;
  MaxEndurance = 100.f;
  EnduranceRegenRate = 0.5f;

  Strength = 10.0f;
  Dexterity = 10.0f;
  Constitution = 10.0f;
  Quickness = 5.0f;
  Intelligence = 10.0f;
  Piety = 10.0f;
  Empathy = 0.0f;
  Charisma = 5.0f;

  CrushResist = 0.0f;
  SlashResist = 0.0f;
  ThrustResist = 0.0f;
  HeatResist = 0.0f;
  ColdResist = 0.0f;
  MatterResist = 0.0f;
  BodyResist = 0.0f;
  SpiritResist = 0.0f;
  EnergyResist = 0.0f;
}

bool UMMOAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
  static UProperty* HealthProperty  = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Health));
  static UProperty* DamageProperty  = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Damage));
  static UProperty* HealingProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Healing));

  UProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();

  // Is Damage about to be applied?
  if (DamageProperty == ModifiedProperty)
  {
    /*
    //Dodge chance
    if (Dodge > 0.f)
    {
      if (FMath::FRand() <= Dodge)
      {
        Data.EvaluatedData.Magnitude = 0.f;
      }
    }

    if (Data.EvaluatedData.Magnitude > 0.f)
    {
      const UMMOAttributeSet* SourceAttributes = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent()->GetSet<UMMOAttributeSet>();
      if (SourceAttributes && SourceAttributes->CritChance > 0.f)
      {
        if (FMath::FRand() <= SourceAttributes->CritChance)
        {
          //This is a Crit!
          Data.EvaluatedData.Magnitude *= SourceAttributes->CritMultiplier;
        }
      }

      Data.EvaluatedData.Magnitude *= (1.f - Defense);
    }*/

    AMMOCharacterAbilities* mmoCharacter = CastChecked<AMMOCharacterAbilities>(GetOwningActor());
    float NewMagnitude = Data.EvaluatedData.Magnitude;
    bool IsCritical = false;
    const UMMOAttributeSet* SourceAttributes = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent()->GetSet<UMMOAttributeSet>();

    WhoAttackedUsLast = Cast<AMMOCharacterAbilities>(Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent()->GetOwner());

    FGameplayTagContainer EffectTags;
    Data.EffectSpec.GetAllAssetTags(EffectTags);

    mmoCharacter->OnAttacked(WhoAttackedUsLast);

    mmoCharacter->CalculateUpdatedDamage(Data.EvaluatedData.Magnitude, SourceAttributes, EffectTags, NewMagnitude, IsCritical);

    // A * (X + B) + C
    // X = Intellect
    // A = Coefficient
    // B = Pre-Multiply Additive
    // C = Post Multiply Additive

    Data.EvaluatedData.Magnitude = NewMagnitude;

    if (NewMagnitude > 0.f)
    {
      AMMOCharacterAbilities* DamagedCharacter = Cast<AMMOCharacterAbilities>(GetOwningActor());
      if (DamagedCharacter)
      {
        DamagedCharacter->OnTakeDamage(WhoAttackedUsLast, NewMagnitude, IsCritical);

        UE_LOG(LogTemp, Warning, TEXT("%s took Damage : %f"), *DamagedCharacter->GetName(), NewMagnitude);

        if (WhoAttackedUsLast)
        {
          AMMOCharacterAbilities* AttackingCharacter = WhoAttackedUsLast;

          if (AttackingCharacter)
          {
            AttackingCharacter->OnInflictDamage(DamagedCharacter, NewMagnitude, IsCritical);
          }
        }
      }
    }
  }

  return true;
}

void UMMOAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
  static UProperty* DamageProperty    = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Damage));
  static UProperty* HealingProperty   = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Healing));
  static UProperty* ManaProperty      = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Mana));
  static UProperty* EnduranceProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Endurance));

  UProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();

  // What property was modified?
  if (DamageProperty == ModifiedProperty)
  {
    // Treat damage as minus health
    SetHealth(FMath::Clamp(GetHealth() - Damage.GetCurrentValue(), 0.f, GetMaxHealth()));
    Damage = 0.f;
    UE_LOG(LogTemp, Warning, TEXT("Damage!"));
  }

  if (HealingProperty == ModifiedProperty)
  {
    SetHealth(FMath::Clamp(GetHealth() + Healing.GetCurrentValue(), 0.f, GetMaxHealth()));
    Healing = 0.f;

    UE_LOG(LogTemp, Warning, TEXT("HEALING!"));
  }

  if (ManaProperty == ModifiedProperty)
  {
    SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
    //Mana.SetBaseValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, Mana.GetCurrentValue()));
    //Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
    //Mana = FMath::Clamp(Mana, 0.f, MaxMana);
  }

  if (EnduranceProperty == ModifiedProperty)
  {
    SetEndurance(FMath::Clamp(GetEndurance(), 0.f, GetMaxEndurance()));
    //Endurance.SetCurrentValue(FMath::Clamp(Endurance.GetCurrentValue(), 0.f, MaxEndurance.GetCurrentValue()));
    //Endurance = FMath::Clamp(Endurance, 0.f, MaxEndurance);
  }

  //Dead
  if (GetHealth() <= 0.f)
  {
    FName DeadTagName = FName(TEXT("Combat.State.Dead"));
    FGameplayTag DeadTag = UGameplayTagsManager::Get().RequestGameplayTag(DeadTagName);

    AMMOCharacterAbilities* mmoCharacter = Cast<AMMOCharacterAbilities>(GetOwningActor());
    if (mmoCharacter && !mmoCharacter->GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(FGameplayTagContainer(DeadTag)))
    {
      UE_LOG(LogTemp, Warning, TEXT("DEAD!"));

      mmoCharacter->Die(WhoAttackedUsLast);
      mmoCharacter->OnDeath(WhoAttackedUsLast);
    }
  }

}

void UMMOAttributeSet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  // Health, Mana and Endurance
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Health, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);

  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Mana, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, ManaRegenRate, COND_None, REPNOTIFY_Always);

  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, MaxEndurance, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, EnduranceRegenRate, COND_None, REPNOTIFY_Always);


  // Stats
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Strength, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Constitution, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Quickness, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Piety, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Empathy, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, Charisma, COND_None, REPNOTIFY_Always);

  // Resists
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, CrushResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, SlashResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, ThrustResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, HeatResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, ColdResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, MatterResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, BodyResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, SpiritResist, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, EnergyResist, COND_None, REPNOTIFY_Always);

  // AF, DPS
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, ArmorFactor, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, DamagePerSecond, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSet, ArmorAbsorption, COND_None, REPNOTIFY_Always);
  
}
