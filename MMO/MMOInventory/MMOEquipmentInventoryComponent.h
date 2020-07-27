// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMO/MMOInventory/MMOInventoryComponent.h"
#include "MMOEquipmentInventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API UMMOEquipmentInventoryComponent : public UMMOInventoryComponent
{
	GENERATED_BODY()

public:
  // Server:  In An Equipment Inventory The First Set Of Inventory Slots Are Equipment Slots, So We Need To Handle It Differently
  virtual void InitializeInventory(int32 InventorySize) override;

  // Server: Set The Inventory Item At given index
  virtual void SetItem(int32 InventorySlot, const FInventoryItem& Item) override;

  // Server: Returns The Inventory Item From The Inventory
  FInventoryItem GetItemInSlot(EEquipmentSlots Slot);

  // Server: Clears The Inventory Item From The Inventory
  virtual void ClearItem(int32 InventorySlot) override;

  // Server: Returns The First Available Inventory Space
  virtual bool GetFirstEmptyInventorySlot(int32& OutSlot) override;

  // Server: Clears The Inventory and Fills It With The Loaded Items
  virtual void LoadGivenInventoryItems(const TArray<FInventoryItem> InventoryItems, int32 InventorySize) override;

  void UpdateEquipment(int32 InventorySlot);
};
