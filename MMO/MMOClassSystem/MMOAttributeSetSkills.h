// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MMOAttributeSetSkills.generated.h"

/**
 * This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
 * It would creates the following functions, for attribute TwoHanded
 *
 *	static FGameplayAttribute UMyTwoHandedSet::GetTwoHandedAttribute();
 *	FORCEINLINE float UMyTwoHandedSet::GetTwoHanded() const;
 *	FORCEINLINE void UMyTwoHandedSet::SetTwoHanded(float NewVal);
 *	FORCEINLINE void UMyTwoHandedSet::InitTwoHanded(float NewVal);
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
UCLASS()
class MMO_API UMMOAttributeSetSkills : public UAttributeSet
{
  GENERATED_UCLASS_BODY()
	
  //Two Handed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_TwoHanded, Category = SkillAttributes, meta = (HideFromModifiers))
  FGameplayAttributeData TwoHanded;
  UFUNCTION()
  void OnRep_TwoHanded() { GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOAttributeSetSkills, TwoHanded); }
  ATTRIBUTE_ACCESSORS(UMMOAttributeSetSkills, TwoHanded)
  UFUNCTION(BlueprintCallable, Category = SkillAttributes)
  float MMOGetTwoHanded() const
  {
    return TwoHanded.GetCurrentValue();
  }
  UFUNCTION(BlueprintCallable, Category = SkillAttributes)
  void MMOSetTwoHanded(float NewVal)
  {
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (ensure(AbilityComp))
    {
      AbilityComp->SetNumericAttributeBase(GetTwoHandedAttribute(), NewVal);
    };
  }
  UFUNCTION(BlueprintCallable, Category = SkillAttributes)
    void MMOInitTwoHanded(float NewVal)
  {
    TwoHanded.SetBaseValue(NewVal);
    TwoHanded.SetCurrentValue(NewVal);
  }


};
