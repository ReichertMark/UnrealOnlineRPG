// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Core/Public/Misc/Guid.h"
#include "MMOCharacterMovementComponent.h"
#include "MMOClassSystem/MMOCharacterClass.h"
#include "MMOAbilities/MMOAbilityTypes.h"
#include <Abilities/GameplayAbility.h>
#include "MMOCharacter.generated.h"






UCLASS()
class AMMOCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMMOCharacter(const class FObjectInitializer& ObjectInitializer);


  UPROPERTY(BlueprintReadWrite, Category = "Config")
  FString WebApiPath = "";

  UPROPERTY(BlueprintReadWrite, Category = "Input")
  bool bDisableMouseRotation;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mob)
  bool IsAMob;


  UFUNCTION(BlueprintCallable, Category = "Movement")
  FORCEINLINE class UMMOCharacterMovementComponent* GetMMOMovementComponent() const { return MMOCharacterMovementComponent; }

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internal")
  bool IsTransferringBetweenMaps;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

  // APawn interface
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
  virtual void PossessedBy(AController* NewController) override;
  virtual void PostInitializeComponents() override;
	// End of APawn interface


  // --- Abilities ---
  UFUNCTION(BlueprintCallable, Category = "Abilities")
  void GetCharacterAbilities();

  UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
  void GetCharacterAbilitiesComplete(const TArray<FString>& SkillIDs);


  // MMOCharacter interface
  virtual void LoadCharacterData();
  virtual void LoadCharacterDataFromJSON(TSharedPtr<FJsonObject> JsonObject);

  // --- Character Data ---
    // Set Character Class Trigger
  UFUNCTION(BlueprintImplementableEvent, Category = "CharacterClass")
    void OnSetCharacterClass(ECharacterClass ClassToSet);

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterClass")
    TSubclassOf<class UMMOCharacterClass> CharacterClass;


  // Common Data
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  FString CharacterName;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 AccountSlot;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Gender;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Race;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Class;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Realm;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Region;

  // Appearance
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Model;

  // Experience 
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Level;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int64 Experience;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 RealmLevel;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int64 RealmPoints;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int64 BountyPoints;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Copper;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Silver;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Gold;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", Replicated)
  int32 Platinum;

  // Stats
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Strength;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Dexterity;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Constitution;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Quickness;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Intelligence;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Piety;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Empathy;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Charisma;

  // Resistances
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float CrushResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float SlashResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float ThrustResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float HeatResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float ColdResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float MatterResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float BodyResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float SpiritResist;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float EnergyResist;

  // Bind Data
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindData", Replicated)
  float BindPosX;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindData", Replicated)
  float BindPosY;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindData", Replicated)
  float BindPosZ;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindData", Replicated)
  float BindRotX;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindData", Replicated)
  float BindRotY;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindData", Replicated)
  float BindRotZ;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindData", Replicated)
  int BindRegion;

  // Health, Mana and Endurance
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float MaxHealth;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Health;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float HealthRegenRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float MaxMana;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Mana;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float ManaRegenRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float MaxEndurance;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float Endurance;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats", Replicated)
  float EnduranceRegenRate;


protected:
  FHttpModule* Http;

private:
  UMMOCharacterMovementComponent* MMOCharacterMovementComponent;

};

