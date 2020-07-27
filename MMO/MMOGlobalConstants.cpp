// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOGlobalConstants.h"
#include <GameplayTagsManager.h>


const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotRightHandWeapon = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.RightHandWeapon")));
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotLeftHandWeapon  = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.LeftHandWeapon")));
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotTwoHandWeapon   = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.TwoHandWeapon")));
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotDistanceWeapon  = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.DistanceWeapon")));
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotHead            = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Head")));
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotHands           = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Hands")));
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotFeet            = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Feet")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotJewellery       = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Jewellery")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotChest           = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Chest")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotCloak           = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Cloak")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotLegs            = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Legs")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotArms            = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Arms")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotNeck            = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Neck")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotWaist           = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.Waist")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotLeftBracer      = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.LeftBracer")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotRightBracer     = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.RightBracer")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotLeftRing        = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.LeftRing")));;
const FGameplayTag UMMOGlobalConstants::TagEquipmentSlotRightRing       = UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("Equipment.Slot.RightRing")));;


FGameplayTag UMMOGlobalConstants::GetEquipmentTagForSlot(EEquipmentSlots EquipmentSlot)
{
  switch (EquipmentSlot)
  {
  case EEquipmentSlots::Chest:            return TagEquipmentSlotChest;
  case EEquipmentSlots::Arms:             return TagEquipmentSlotArms;
  case EEquipmentSlots::Jewellery:        return TagEquipmentSlotJewellery;
  case EEquipmentSlots::LeftRing:         return TagEquipmentSlotLeftRing;
  case EEquipmentSlots::LeftBracer:       return TagEquipmentSlotLeftBracer;
  case EEquipmentSlots::Legs:             return TagEquipmentSlotLegs;
  case EEquipmentSlots::Head:             return TagEquipmentSlotHead;
  case EEquipmentSlots::Hands:            return TagEquipmentSlotHands;
  case EEquipmentSlots::Waist:            return TagEquipmentSlotWaist;
  case EEquipmentSlots::RightRing:        return TagEquipmentSlotRightRing;
  case EEquipmentSlots::RightBracer:      return TagEquipmentSlotRightBracer;
  case EEquipmentSlots::Feet:             return TagEquipmentSlotFeet;
  case EEquipmentSlots::Neck:             return TagEquipmentSlotNeck;
  case EEquipmentSlots::Cloak:            return TagEquipmentSlotCloak;
  case EEquipmentSlots::RightHandWeapon:  return TagEquipmentSlotRightHandWeapon;
  case EEquipmentSlots::LeftHandWeapon:   return TagEquipmentSlotLeftHandWeapon;
  case EEquipmentSlots::TwoHandWeapon:    return TagEquipmentSlotTwoHandWeapon;
  case EEquipmentSlots::DistanceWeapon:   return TagEquipmentSlotDistanceWeapon;

  case EEquipmentSlots::Count:
  default:
    UE_LOG(LogTemp, Error, TEXT("UMMOGlobalConstants: GetEquipmentTagForSlot - Invalid Slot specified!"));
    return TagEquipmentSlotChest;
    break;

  }
}

bool UMMOGlobalConstants::IsWeaponSlot(EEquipmentSlots EquipmentSlot)
{
  return (EquipmentSlot == EEquipmentSlots::RightHandWeapon ||
          EquipmentSlot == EEquipmentSlots::LeftHandWeapon  ||
          EquipmentSlot == EEquipmentSlots::TwoHandWeapon   ||
          EquipmentSlot == EEquipmentSlots::DistanceWeapon   );
}

TMap<EStat, int> UMMOGlobalConstants::GetStartingStatsForRace(ERace race)
{
	TMap<EStat, int> sm;

	switch (race)
	{
		// Britons
	case ERace::Briton:		  sm = { {EStat::Strength, 60},  {EStat::Constitution, 60}, {EStat::Dexterity, 60}, {EStat::Quickness, 60}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Avalonian:	sm = { {EStat::Strength, 45},  {EStat::Constitution, 45}, {EStat::Dexterity, 60}, {EStat::Quickness, 70}, {EStat::Intelligence, 80}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Highlander:	sm = { {EStat::Strength, 70},  {EStat::Constitution, 70}, {EStat::Dexterity, 50}, {EStat::Quickness, 50}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Saracen:    sm = { {EStat::Strength, 50},  {EStat::Constitution, 50}, {EStat::Dexterity, 80}, {EStat::Quickness, 60}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;

		// Vikings
	case ERace::Norseman:	  sm = { {EStat::Strength, 70},  {EStat::Constitution, 70}, {EStat::Dexterity, 50}, {EStat::Quickness, 50}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Troll:		  sm = { {EStat::Strength, 100}, {EStat::Constitution, 70}, {EStat::Dexterity, 35}, {EStat::Quickness, 35}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Dwarf:		  sm = { {EStat::Strength, 60},  {EStat::Constitution, 80}, {EStat::Dexterity, 50}, {EStat::Quickness, 50}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Kobold:		  sm = { {EStat::Strength, 50},  {EStat::Constitution, 50}, {EStat::Dexterity, 70}, {EStat::Quickness, 70}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;

		// Celts
	case ERace::Celt:		    sm = { {EStat::Strength, 60},  {EStat::Constitution, 60}, {EStat::Dexterity, 60}, {EStat::Quickness, 60}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Firbolg:	  sm = { {EStat::Strength, 90},  {EStat::Constitution, 60}, {EStat::Dexterity, 40}, {EStat::Quickness, 40}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 70}, {EStat::Charisma, 60}, }; break;
	case ERace::Elf:		    sm = { {EStat::Strength, 40},  {EStat::Constitution, 40}, {EStat::Dexterity, 75}, {EStat::Quickness, 75}, {EStat::Intelligence, 70}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;
	case ERace::Lurikeen:	  sm = { {EStat::Strength, 40},  {EStat::Constitution, 40}, {EStat::Dexterity, 80}, {EStat::Quickness, 80}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, }; break;

		// Error
	default:
	case ERace::Count:
	case ERace::Undefined:	sm = { {EStat::Strength, 60},  {EStat::Constitution, 60}, {EStat::Dexterity, 60}, {EStat::Quickness, 60}, {EStat::Intelligence, 60}, {EStat::Piety, 60}, {EStat::Empathy, 60}, {EStat::Charisma, 60}, };
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities::GetStartingStatsForRace - Undefined race"));
		break;
	}

	return sm;
}


TArray<ECharacterClass> UMMOGlobalConstants::GetClassesForRealm(ERealm realm)
{
	TArray<ECharacterClass> cl;

	switch (realm)
	{
	case ERealm::Britons:
		cl = 
		{ 
			ECharacterClass::Paladin,
			ECharacterClass::Armsman,
			ECharacterClass::Scout,
			ECharacterClass::Minstrel,
			ECharacterClass::Theurgist,
			ECharacterClass::Cleric,
			ECharacterClass::Wizard,
			ECharacterClass::Sorcerer,
			ECharacterClass::Infiltrator,
			ECharacterClass::Friar,
			ECharacterClass::Mercenary,
			ECharacterClass::Cabalist,
		};
		break;
	case ERealm::Vikings:
		cl =
		{
			ECharacterClass::Thane,
			ECharacterClass::Warrior,
			ECharacterClass::Shadowblade,
			ECharacterClass::Skald,
			ECharacterClass::Hunter,
			ECharacterClass::Healer,
			ECharacterClass::Spiritmaster,
			ECharacterClass::Shaman,
			ECharacterClass::Runemaster,
			ECharacterClass::Berserker,
		};
		break;
	case ERealm::Celts:
		cl =
		{
			ECharacterClass::Eldritch,
			ECharacterClass::Enchanter,
			ECharacterClass::Mentalist,
			ECharacterClass::Blademaster,
			ECharacterClass::Hero,
			ECharacterClass::Champion,
			ECharacterClass::Warden,
			ECharacterClass::Druid,
			ECharacterClass::Bard,
			ECharacterClass::Nightshade,
			ECharacterClass::Ranger,
		};
		break;

	default:
		break;
	}

	return cl;
}


TArray<ECharacterClass> UMMOGlobalConstants::GetClassesForRace(ERace race)
{
	TArray<ECharacterClass> cl;

	switch (race)
	{
		// Britons
	case ERace::Briton:		
		cl = 
		{
			ECharacterClass::Armsman,
			ECharacterClass::Mercenary,
			ECharacterClass::Paladin,
			ECharacterClass::Cleric,
			ECharacterClass::Friar,
			ECharacterClass::Sorcerer,
			ECharacterClass::Cabalist,
			ECharacterClass::Theurgist,
			ECharacterClass::Wizard,
			ECharacterClass::Minstrel,
			ECharacterClass::Infiltrator,
			ECharacterClass::Scout,
		};
		break;
	case ERace::Avalonian:	
		cl =
		{
			ECharacterClass::Paladin,
			ECharacterClass::Cleric,
			ECharacterClass::Wizard,
			ECharacterClass::Theurgist,
			ECharacterClass::Armsman,
			ECharacterClass::Mercenary,
			ECharacterClass::Sorcerer,
			ECharacterClass::Cabalist,
			ECharacterClass::Friar,
		};
		break;
	case ERace::Highlander:	
		cl =
		{
			ECharacterClass::Armsman,
			ECharacterClass::Mercenary,
			ECharacterClass::Paladin,
			ECharacterClass::Cleric,
			ECharacterClass::Minstrel,
			ECharacterClass::Scout,
			ECharacterClass::Friar,
		};
		break;
	case ERace::Saracen: 
		cl =
		{
			ECharacterClass::Sorcerer,
			ECharacterClass::Cabalist,
			ECharacterClass::Paladin,
			ECharacterClass::Mercenary,
			ECharacterClass::Armsman,
			ECharacterClass::Infiltrator,
			ECharacterClass::Minstrel,
			ECharacterClass::Scout,
		};
		break;

		// Vikings
	case ERace::Norseman:	
		cl =
		{
			ECharacterClass::Healer,
			ECharacterClass::Warrior,
			ECharacterClass::Berserker,
			ECharacterClass::Thane,
			ECharacterClass::Skald,
			ECharacterClass::Spiritmaster,
			ECharacterClass::Runemaster,
			ECharacterClass::Shadowblade,
			ECharacterClass::Hunter,
		};
		break;
	case ERace::Troll:		
		cl =
		{
			ECharacterClass::Berserker,
			ECharacterClass::Warrior,
			ECharacterClass::Thane,
			ECharacterClass::Skald,
			ECharacterClass::Shaman,
		};
		break;
	case ERace::Dwarf:		
		cl =
		{
			ECharacterClass::Healer,
			ECharacterClass::Thane,
			ECharacterClass::Berserker,
			ECharacterClass::Warrior,
			ECharacterClass::Skald,
			ECharacterClass::Runemaster,
			ECharacterClass::Hunter,
			ECharacterClass::Shaman,
		};
		break;
	case ERace::Kobold:		
		cl =
		{ 
			ECharacterClass::Shaman,
			ECharacterClass::Warrior,
			ECharacterClass::Skald,
			ECharacterClass::Runemaster,
			ECharacterClass::Spiritmaster,
			ECharacterClass::Hunter,
			ECharacterClass::Shadowblade,
		};
		break;

		// Celts
	case ERace::Celt:		
		cl =
		{ 
			ECharacterClass::Bard,
			ECharacterClass::Druid,
			ECharacterClass::Warden,
			ECharacterClass::Blademaster,
			ECharacterClass::Hero,
			ECharacterClass::Champion,
			ECharacterClass::Mentalist,
			ECharacterClass::Ranger,
			ECharacterClass::Nightshade,
		};
		break;
	case ERace::Firbolg:	
		cl =
		{
			ECharacterClass::Bard,
			ECharacterClass::Druid,
			ECharacterClass::Warden,
			ECharacterClass::Hero,
			ECharacterClass::Blademaster,
		};
		break;
	case ERace::Elf:		
		cl =
		{
			ECharacterClass::Blademaster,
			ECharacterClass::Champion,
			ECharacterClass::Ranger,
			ECharacterClass::Nightshade,
			ECharacterClass::Enchanter,
			ECharacterClass::Eldritch,
			ECharacterClass::Mentalist,
		};
		break;
	case ERace::Lurikeen:	
		cl =
		{
			ECharacterClass::Hero,
			ECharacterClass::Champion,
			ECharacterClass::Eldritch,
			ECharacterClass::Enchanter,
			ECharacterClass::Mentalist,
			ECharacterClass::Nightshade,
			ECharacterClass::Ranger,
		};
		break;

		// Should not Happen
	default:
	case ERace::Count:
	case ERace::Undefined:	
		break;
	}

	return cl;
}


bool UMMOGlobalConstants::IsCustomPointDistributionValid(ERace race, int level, TMap<EStat, int> stats)
{
  int pointsLeft = 0;

  TMap<EStat, int> raceStats = GetStartingStatsForRace(race);

  for (auto& currentStat : stats)
  {
    int* pRaceAmount = raceStats.Find(currentStat.Key);
    
    // could not find the stat
    if (pRaceAmount == nullptr) 
      return false;


    // TODO: use level and class to figure out the class amount for each level
    int classAmount = 0;

    int raceAmount = *pRaceAmount;

    int difference = currentStat.Value - raceAmount - classAmount;

    // negative difference should not occur
    if (difference < 0) 
      return false;

    pointsLeft += difference;
    pointsLeft += FMath::Max<int>(0, difference - 10); //two points used
    pointsLeft += FMath::Max<int>(0, difference - 15); //three points used
  }

  return pointsLeft == 30;

}

