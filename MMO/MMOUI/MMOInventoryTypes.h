// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayTagContainer.h>
#include <Engine/DataTable.h>
#include <Abilities/GameplayAbility.h>
#include "MMO/MMOGlobalConstants.h"
#include "MMOInventoryTypes.generated.h"


UENUM(BlueprintType)
enum class EItemQuality : uint8
{
  Poor UMETA(DisplayName = "Poor"), 
  Common UMETA(DisplayName = "Common"), 
  Uncommon UMETA(DisplayName = "Uncommon"),
  Rare UMETA(DisplayName = "Rare"),
  Epic UMETA(DisplayName = "Epic"),
  Legendary UMETA(DisplayName = "Legendary")
};


// eWeaponDamageType


USTRUCT(BlueprintType)
struct MMO_API FItemInformation
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
  FString ID;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
  UTexture2D* Icon = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
  FName Name;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
  EItemQuality Quality;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
  EObjectType ItemType;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
  int Amount;

  // used for Abilities in Action Bar
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
  TSubclassOf<UGameplayAbility> Ability;

};


USTRUCT(BlueprintType)
struct MMO_API FInventoryItem : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  FString ID;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  FName Name;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  FString Description;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  FGameplayTag EquipmentSlot;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  UTexture2D* Icon = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  UStaticMesh* WorldMesh = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  USkeletalMesh* EquipmentMesh = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  EItemQuality Quality;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  EObjectType ItemType;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  int Amount;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  bool IsStackable;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  int MaxStackSize;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
  bool IsDroppable;


  // Attributes
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Strength;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Dexterity;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Constitution;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Quickness;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Intelligence;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Piety;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Empathy;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
  float Charisma;
  
  // Resistances
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float CrushResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float SlashResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float ThrustResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float HeatResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float ColdResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float MatterResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float BodyResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float SpiritResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
  float EnergyResist;
};
