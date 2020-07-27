// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MMOCharacter.h"
#include "Net/UnrealNetwork.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include <Misc/ConfigCacheIni.h>


AMMOCharacter::AMMOCharacter(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer.SetDefaultSubobjectClass<UMMOCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  IsTransferringBetweenMaps = false;

  Http = &FHttpModule::Get();

  GConfig->GetString(
    TEXT("/Script/EngineSettings.GeneralProjectSettings"),
    TEXT("WebApiPath"),
    WebApiPath,
    GGameIni
  );
}

void AMMOCharacter::BeginPlay()
{
  Super::BeginPlay();
}

void AMMOCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void AMMOCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMMOCharacter::PossessedBy(AController* NewController)
{
  Super::PossessedBy(NewController);

  if (Role == ROLE_Authority)
  {
    if (!IsAMob)
    {
      LoadCharacterData();
    }
  }
}

void AMMOCharacter::PostInitializeComponents()
{
  Super::PostInitializeComponents();

  MMOCharacterMovementComponent = Cast<UMMOCharacterMovementComponent>(Super::GetMovementComponent());
}

void AMMOCharacter::GetCharacterAbilities()
{
  TArray<FString> Abilities;
  Abilities.Add("GleamRay");
  Abilities.Add("GleamStreak");
  Abilities.Add("GleamBlast");
  Abilities.Add("PristmaticFlare");

  GetCharacterAbilitiesComplete(Abilities);
}

void AMMOCharacter::LoadCharacterData()
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacter: LoadCharacterData"));

}

void AMMOCharacter::LoadCharacterDataFromJSON(TSharedPtr<FJsonObject> JsonObject)
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacter: LoadCharacterDataFromJSON"));

  // Common Data
  CharacterName = JsonObject->GetStringField("Name");
  AccountSlot = JsonObject->GetNumberField("AccountSlot");
  Gender = JsonObject->GetNumberField("Gender");
  Race = JsonObject->GetNumberField("Race");
  Class = JsonObject->GetNumberField("Class");
  Realm = JsonObject->GetNumberField("Realm");
  Region = JsonObject->GetNumberField("Region");

  // Appearance
  Model = JsonObject->GetNumberField("Model");

  // Experience
  Level = JsonObject->GetNumberField("Level");
  Experience = JsonObject->GetNumberField("Experience");
  RealmLevel = JsonObject->GetNumberField("RealmLevel");
  RealmPoints = JsonObject->GetNumberField("RealmPoints");
  BountyPoints = JsonObject->GetNumberField("BountyPoints");

  // Currency
  Copper = JsonObject->GetNumberField("Copper");
  Silver = JsonObject->GetNumberField("Silver");
  Gold = JsonObject->GetNumberField("Gold");
  Platinum = JsonObject->GetNumberField("Platinum");

  // Stats
  Strength = JsonObject->GetNumberField("Strength");
  Dexterity = JsonObject->GetNumberField("Dexterity");
  Constitution = JsonObject->GetNumberField("Constitution");
  Quickness = JsonObject->GetNumberField("Quickness");
  Intelligence = JsonObject->GetNumberField("Intelligence");
  Piety = JsonObject->GetNumberField("Piety");
  Empathy = JsonObject->GetNumberField("Empathy");
  Charisma = JsonObject->GetNumberField("Charisma");

  // Resists, skipped



  // Bind Data
  BindPosX = JsonObject->GetNumberField("BindPosX");
  BindPosY = JsonObject->GetNumberField("BindPosY");
  BindPosZ = JsonObject->GetNumberField("BindPosZ");
  BindRotX = JsonObject->GetNumberField("BindRotX");
  BindRotY = JsonObject->GetNumberField("BindRotY");
  BindRotZ = JsonObject->GetNumberField("BindRotZ");
  BindRegion = JsonObject->GetNumberField("BindRegion");


  OnSetCharacterClass((ECharacterClass)Class);

  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacter: LoadCharacterDataFromJSON Race:%d"), Race);

}

void AMMOCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  // --- Character Data ---

  // Common Data
  DOREPLIFETIME(AMMOCharacter, CharacterName); 
  DOREPLIFETIME(AMMOCharacter, AccountSlot);
  DOREPLIFETIME(AMMOCharacter, Gender);
  DOREPLIFETIME(AMMOCharacter, Race);
  DOREPLIFETIME(AMMOCharacter, Class);
  DOREPLIFETIME(AMMOCharacter, Realm);
  DOREPLIFETIME(AMMOCharacter, Region);

  // Appearance
  DOREPLIFETIME(AMMOCharacter, Model);

  // Experience
  DOREPLIFETIME(AMMOCharacter, Level);
  DOREPLIFETIME(AMMOCharacter, Experience);
  DOREPLIFETIME(AMMOCharacter, RealmLevel);
  DOREPLIFETIME(AMMOCharacter, RealmPoints);
  DOREPLIFETIME(AMMOCharacter, BountyPoints);

  // Currenty
  DOREPLIFETIME(AMMOCharacter, Copper);
  DOREPLIFETIME(AMMOCharacter, Silver);
  DOREPLIFETIME(AMMOCharacter, Gold);
  DOREPLIFETIME(AMMOCharacter, Platinum);

  // stats
  DOREPLIFETIME(AMMOCharacter, Strength);
  DOREPLIFETIME(AMMOCharacter, Dexterity);
  DOREPLIFETIME(AMMOCharacter, Constitution);
  DOREPLIFETIME(AMMOCharacter, Quickness);
  DOREPLIFETIME(AMMOCharacter, Intelligence);
  DOREPLIFETIME(AMMOCharacter, Piety);
  DOREPLIFETIME(AMMOCharacter, Empathy);
  DOREPLIFETIME(AMMOCharacter, Charisma);

  // Resistances
  DOREPLIFETIME(AMMOCharacter, CrushResist);
  DOREPLIFETIME(AMMOCharacter, SlashResist);
  DOREPLIFETIME(AMMOCharacter, ThrustResist);
  DOREPLIFETIME(AMMOCharacter, HeatResist);
  DOREPLIFETIME(AMMOCharacter, ColdResist);
  DOREPLIFETIME(AMMOCharacter, MatterResist);
  DOREPLIFETIME(AMMOCharacter, BodyResist);
  DOREPLIFETIME(AMMOCharacter, SpiritResist);
  DOREPLIFETIME(AMMOCharacter, EnergyResist);

  // Bind Data
  DOREPLIFETIME(AMMOCharacter, BindPosX);
  DOREPLIFETIME(AMMOCharacter, BindPosY);
  DOREPLIFETIME(AMMOCharacter, BindPosZ);
  DOREPLIFETIME(AMMOCharacter, BindRotX);
  DOREPLIFETIME(AMMOCharacter, BindRotY);
  DOREPLIFETIME(AMMOCharacter, BindRotZ);
  DOREPLIFETIME(AMMOCharacter, BindRegion);


  // Health, Mana and Endurance
  DOREPLIFETIME(AMMOCharacter, MaxHealth);
  DOREPLIFETIME(AMMOCharacter, Health);
  DOREPLIFETIME(AMMOCharacter, HealthRegenRate);

  DOREPLIFETIME(AMMOCharacter, MaxMana);
  DOREPLIFETIME(AMMOCharacter, Mana);
  DOREPLIFETIME(AMMOCharacter, ManaRegenRate);

  DOREPLIFETIME(AMMOCharacter, MaxEndurance);
  DOREPLIFETIME(AMMOCharacter, Endurance);
  DOREPLIFETIME(AMMOCharacter, EnduranceRegenRate);
}
