// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOEquipmentInventoryComponent.h"
#include "MMO/MMOCharacterAbilities.h"

void UMMOEquipmentInventoryComponent::InitializeInventory(int32 InventorySize)
{
  Super::InitializeInventory((int32)EEquipmentSlots::Count + InventorySize);
}

void UMMOEquipmentInventoryComponent::SetItem(int32 InventorySlot, const FInventoryItem& Item)
{
  Super::SetItem(InventorySlot, Item);

  UpdateEquipment(InventorySlot);
}

FInventoryItem UMMOEquipmentInventoryComponent::GetItemInSlot(EEquipmentSlots Slot)
{
  return GetItem((int32)Slot);
}

void UMMOEquipmentInventoryComponent::ClearItem(int32 InventorySlot)
{
  Super::ClearItem(InventorySlot);

  UpdateEquipment(InventorySlot);
}

bool UMMOEquipmentInventoryComponent::GetFirstEmptyInventorySlot(int32& OutSlot)
{
  OutSlot = 0;

  for (int32 InventorySlot = 0; InventorySlot != Inventory.Num(); ++InventorySlot)
  {
    const FInventoryItem& Item = Inventory[InventorySlot];
    if (IsItemValid(Item) == false &&
      InventorySlot >= (int32)EEquipmentSlots::Count) // first slots are equipment slots
    {
      OutSlot = InventorySlot;

      return true;
    }
  }

  return false;
}

void UMMOEquipmentInventoryComponent::LoadGivenInventoryItems(const TArray<FInventoryItem> InventoryItems, int32 InventorySize)
{
  Super::LoadGivenInventoryItems(InventoryItems, (int32)EEquipmentSlots::Count + InventorySize);
}

void UMMOEquipmentInventoryComponent::UpdateEquipment(int32 InventorySlot)
{

  AMMOCharacterAbilities* Character = Cast<AMMOCharacterAbilities>(GetOwner());

  if (Character)
  {
    if (InventorySlot < (int32)EEquipmentSlots::Count)
    {

      UE_LOG(LogTemp, Warning, TEXT("UMMOEquipmentInventoryComponent: UpdateEquipment %d"), InventorySlot);

      FInventoryItem item = GetItem(InventorySlot);
      EEquipmentSlots EquipmentSlot = (EEquipmentSlots)InventorySlot;

      if (item.Icon != nullptr)
      {
        // Equip
        Character->Equip(item);
      }
      else
      {
        // Unequip
        FGameplayTag TagEquipmentSlot = UMMOGlobalConstants::GetEquipmentTagForSlot(EquipmentSlot);

        Character->Unequip(TagEquipmentSlot, true);
      }

      // Switch Active Weapon if this is a weapon slot

      if (UMMOGlobalConstants::IsWeaponSlot(EquipmentSlot))
      {
        if (EquipmentSlot == EEquipmentSlots::LeftHandWeapon || EquipmentSlot == EEquipmentSlots::RightHandWeapon)
        {
          Character->SwitchActiveWeapon(EActiveWeaponSlot::Standard);
        }
        else if (EquipmentSlot == EEquipmentSlots::TwoHandWeapon)
        {
          Character->SwitchActiveWeapon(EActiveWeaponSlot::TwoHanded);
        }
        else if (EquipmentSlot == EEquipmentSlots::DistanceWeapon)
        {
          Character->SwitchActiveWeapon(EActiveWeaponSlot::Distance);
        }
      }

    }
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("UMMOEquipmentInventoryComponent: UpdateEquipment Character NOT Valid"));
  }

}
