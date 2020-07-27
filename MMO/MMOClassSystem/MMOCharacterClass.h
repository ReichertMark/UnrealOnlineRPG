// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UObject/Object.h>
#include "MMO/MMOGlobalConstants.h"
#include "MMOCharacterClass.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class MMO_API UMMOCharacterClass : public UObject
{
  GENERATED_BODY()

public:
  UMMOCharacterClass(const class FObjectInitializer& ObjectInitializer);

  // ID of the Character Class
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    ECharacterClass ID = ECharacterClass::Undefined;

  // The class type
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    EClassType ClassType = EClassType::Undefined;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    FString MaleName = "UndefinedMaleName";

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    FString FemaleName = "UndefinedFemaleName";

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    FString BaseClassName = "UndefinedBaseClassName";

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    FString Profession = "Undefined";

  // multiplier for specialization points per level in 10th
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    int32 SpecializationMultiplier = 10;

  // BaseHP for hp calculation
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    int32 BaseHP = 600;

  // Stat gained every level.
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    EStat PrimaryStat = EStat::Undefined;

  // Stat gained every second level
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    EStat SecondaryStat = EStat::Undefined;

  // Stat gained every third level.
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    EStat TertiaryStat = EStat::Undefined;

  /// Stat that affects the power/mana pool. set undefined if class has no power pool/spells
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    EStat ManaStat = EStat::Undefined;

  // Weapon Skill Base value to unfluece weapon skill calculation
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    int32 WeaponSkillBase = 400;

  // Weapon Skill Base value to influence ranged weapon skill calculation
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    int32 WeaponSkillBaseRanged = 440;

  // True if this class can use a left handede weapon (e.g. berserker)
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Attributes")
    bool CanUseLeftHandedWeapon = false;
};