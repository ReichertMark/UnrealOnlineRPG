// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "MMO/MMOGlobalConstants.h"
#include "MMO/MMOAbilities/MMOGameplayAbility.h"
#include "MMOAbilityTypes.generated.h"


USTRUCT(BlueprintType)
struct FAbilityRow : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityRow")
  TSubclassOf<UMMOGameplayAbility> Ability;
};

USTRUCT(BlueprintType)
struct FAbilityLine : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityLine")
  FText Name;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityLine")
  bool IsBaseLine;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityLine")
  UDataTable* Abilities;
};


USTRUCT(BlueprintType)
struct FAbilityBarStruct
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Bar Struct")
  int32 AbilityBarID;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Bar Struct")
  FString AbilityBarName;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Bar Struct")
  TArray<FString> Skills;
};