// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOInventoryComponent.h"

// Sets default values for this component's properties
UMMOInventoryComponent::UMMOInventoryComponent()
{
}


void UMMOInventoryComponent::Server_InitializeInventory_Implementation(int32 InventorySize)
{
  InitializeInventory(InventorySize);
}

bool UMMOInventoryComponent::Server_InitializeInventory_Validate(int32 InventorySize)
{
  return true;
}

void UMMOInventoryComponent::InitializeInventory(int32 InventorySize)
{
  //if (GetOwnerRole() == ROLE_Authority)
  {
    Inventory.Empty();
    Inventory.AddDefaulted(InventorySize);
  }
  //else
//   {
//     UE_LOG(LogTemp, Warning, TEXT("UMMOInventoryComponent::InitializeInventory called from Remote. Needs to be called by server."));
//   }
}

FInventoryItem UMMOInventoryComponent::GetItem(int32 InventorySlot)
{
  const FInventoryItem& item = Inventory[InventorySlot];

  if (IsItemValid(item))
  {
    return item;
  }


  return FInventoryItem();
}

void UMMOInventoryComponent::SetItem(int32 InventorySlot, const FInventoryItem& Item)
{
  if (Inventory.Num() - 1 < InventorySlot)
  {
    Inventory.SetNum(InventorySlot);
  }
    
  Inventory[InventorySlot] = Item;
}

void UMMOInventoryComponent::ClearItem(int32 InventorySlot)
{
  Inventory[InventorySlot] = FInventoryItem();
}

bool UMMOInventoryComponent::GetFirstEmptyInventorySlot(int32& OutSlot)
{
  OutSlot = 0;

  for (int32 InventorySlot = 0; InventorySlot != Inventory.Num(); ++InventorySlot)
  {
    const FInventoryItem& Item = Inventory[InventorySlot];
    if (IsItemValid(Item) == false)
    {
      OutSlot = InventorySlot;

      return true;
    }
  }

  return false;
}

int32 UMMOInventoryComponent::GetNumberOfInventoryItems()
{
  int32 NumofInventoryItems = 0;

  for (int32 InventorySlot = 0; InventorySlot != Inventory.Num(); ++InventorySlot)
  {
    const FInventoryItem& Item = Inventory[InventorySlot];
    if (IsItemValid(Item))
    {
      ++NumofInventoryItems;
    }
  }

  return NumofInventoryItems;
}

void UMMOInventoryComponent::IncreaseInventory(int32 Amount)
{
  for (int i = 0; i < Amount; ++i)
  {
    Inventory.Add(FInventoryItem());
  }
}

void UMMOInventoryComponent::DecreaseInventory(int32 Amount)
{
  int32 FirstIndex = Inventory.Num() - Amount;
  int32 LastIndex = Inventory.Num();

  for (int32 index = FirstIndex; index < LastIndex; ++index)
  {
    Inventory.RemoveAt(index);
  }
}

void UMMOInventoryComponent::LoadGivenInventoryItems(const TArray<FInventoryItem> InventoryItems, int32 InventorySize)
{
  Inventory.Empty();
  Inventory.AddDefaulted(InventorySize);

  for (int32 InventorySlot = 0; InventorySlot < InventoryItems.Num(); ++InventorySlot)
  {
    SetItem(InventorySlot, InventoryItems[InventorySlot]);
  }
}

bool UMMOInventoryComponent::IsItemValid(const FInventoryItem& item) const
{
  return item.Icon != nullptr;
}

// Called when the game starts
void UMMOInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


