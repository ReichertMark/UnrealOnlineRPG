// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MMO/MMOUI/MMOInventoryTypes.h"
#include "MMOInventoryComponent.generated.h"



UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MMO_API UMMOInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
  UMMOInventoryComponent();

  UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation, Category = "Inventory")
  void Server_InitializeInventory(int32 InventorySize);

  // Server: Initializes The Inventory Array To A Specified Size
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  virtual void InitializeInventory(int32 InventorySize);

  // Server: Returns The Inventory Item From The Inventory
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  FInventoryItem GetItem(int32 InventorySlot);

  // Server: Set The Inventory Item At given index
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  virtual void SetItem(int32 InventorySlot, const FInventoryItem& Item);

  // Server: Clears The Inventory Item From The Inventory
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  virtual void ClearItem(int32 InventorySlot);

  // Server: Returns The First Available Inventory Space
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  virtual bool GetFirstEmptyInventorySlot(int32& OutSlot);

  // Server: Returns The Number Of Valid Inventory Items
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  int32 GetNumberOfInventoryItems();

  // Server: Adds New Amount To Existing Inventory
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  void IncreaseInventory(int32 Amount);

  // Server: Removes Amount From The End Of The Array
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  void DecreaseInventory(int32 Amount);

  // Server: Clears The Inventory and Fills It With The Loaded Items
  UFUNCTION(BlueprintCallable, Category = "Inventory")
  virtual void LoadGivenInventoryItems(const TArray<FInventoryItem> InventoryItems, int32 InventorySize);

  // Array Of all inventory items
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
  TArray<FInventoryItem> Inventory;

protected:
  // Check if item has an icon assigned if, so, it's defined as valid
  bool IsItemValid(const FInventoryItem& item) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
