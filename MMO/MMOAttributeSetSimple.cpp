// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOAttributeSetSimple.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"
#include "GameplayTagsModule.h"
#include "GameplayEffectExtension.h"

UMMOAttributeSetSimple::UMMOAttributeSetSimple(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{

}

bool UMMOAttributeSetSimple::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
  static UProperty* HealthProperty = FindFieldChecked<UProperty>(UMMOAttributeSetSimple::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSetSimple, Health));
  static UProperty* DamageProperty = FindFieldChecked<UProperty>(UMMOAttributeSetSimple::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSetSimple, Damage));

  return true;
}

void UMMOAttributeSetSimple::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
  static UProperty* DamageProperty = FindFieldChecked<UProperty>(UMMOAttributeSetSimple::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSetSimple, Damage));
  static UProperty* HealingProperty = FindFieldChecked<UProperty>(UMMOAttributeSetSimple::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSetSimple, Healing));

  UProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();


  // What property was modified?
  if (DamageProperty == ModifiedProperty)
  {
    // Treat damage as minus health
    Health -= Damage;
    Health = FMath::Clamp(Health, 0.f, MaxHealth);
    Damage = 0.f;
  }

  if (HealingProperty == ModifiedProperty)
  {
    Health += Healing;
    Health = FMath::Clamp(Health, 0.f, MaxHealth);
    Damage = 0.f;
  }
}

void UMMOAttributeSetSimple::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSetSimple, MaxHealth, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSetSimple, Health, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UMMOAttributeSetSimple, HealthRegenRate, COND_None, REPNOTIFY_Always);
}