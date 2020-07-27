// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <GameplayTagContainer.h>
#include "MMOGlobalConstants.generated.h"


UENUM(BlueprintType)
enum class ERealm : uint8
{
	Britons = 0 UMETA(DisplayName = "Britons"),
	Vikings = 1 UMETA(DisplayName = "Vikings"),
	Celts   = 2 UMETA(DisplayName = "Celts"),
	Count   = 3 UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EGender : uint8
{
	Male	  = 0 UMETA(DisplayName = "Male"),
	Female	= 1 UMETA(DisplayName = "Female"),
	Neutral = 2 UMETA(DisplayName = "Neutral"),
};

UENUM(BlueprintType)
enum class ERace : uint8
{
	Undefined	  =  0 UMETA(DisplayName = "Undefined"),
	// Britons
	Briton		  =  1 UMETA(DisplayName = "Briton"),
	Avalonian	  =  2 UMETA(DisplayName = "Avalonian"),
	Highlander	=  3 UMETA(DisplayName = "Highlander"),
	Saracen		  =  4 UMETA(DisplayName = "Saracen"),
				   
	// Vikings	   
	Norseman	  =  5 UMETA(DisplayName = "Norseman"),
	Troll		    =  6 UMETA(DisplayName = "Troll"),
	Dwarf		    =  7 UMETA(DisplayName = "Dwarf"),
	Kobold		  =  8 UMETA(DisplayName = "Kobold"),
				   
	// Celts	   
	Celt		    =  9 UMETA(DisplayName = "Celt"),
	Firbolg		  = 10 UMETA(DisplayName = "Firbolg"),
	Elf			    = 11 UMETA(DisplayName = "Elf"),
	Lurikeen	  = 12 UMETA(DisplayName = "Lurikeen"),

	Count		    = 13 UMETA(Hidden)
};


UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Undefined		  = 0 UMETA(DisplayName = "Undefined"),

	// Britons
	Armsman			  = 1 UMETA(DisplayName = "Armsman"),
	Cabalist		  = 2 UMETA(DisplayName = "Cabalist"),
	Cleric			  = 3 UMETA(DisplayName = "Cleric"),
	Friar			    = 4 UMETA(DisplayName = "Friar"),
	Infiltrator	  = 5 UMETA(DisplayName = "Infiltrator"),
	Mercenary		  = 6 UMETA(DisplayName = "Mercenary"),
	Minstrel		  = 7 UMETA(DisplayName = "Minstrel"),
	Paladin			  = 8 UMETA(DisplayName = "Paladin"),
	Scout			    = 9 UMETA(DisplayName = "Scout"),
	Sorcerer		  = 10 UMETA(DisplayName = "Sorcerer"),
	Theurgist		  = 11 UMETA(DisplayName = "Theurgist"),
	Wizard			  = 12 UMETA(DisplayName = "Wizard"),

	// Vikings
	Berserker		  = 13 UMETA(DisplayName = "Berserker"),
	Healer			  = 14 UMETA(DisplayName = "Healer"),
	Hunter			  = 15 UMETA(DisplayName = "Hunter"),
	Runemaster	  = 16 UMETA(DisplayName = "Runemaster"),
	Shadowblade	  = 17 UMETA(DisplayName = "Shadowblade"),
	Shaman			  = 18 UMETA(DisplayName = "Shaman"),
	Skald			    = 19 UMETA(DisplayName = "Skald"),
	Spiritmaster	= 20 UMETA(DisplayName = "Spiritmaster"),
	Thane			    = 21 UMETA(DisplayName = "Thane"),
	Warrior			  = 22 UMETA(DisplayName = "Warrior"),

	// celts
	Bard			    = 23 UMETA(DisplayName = "Bard"),
	Blademaster		= 24 UMETA(DisplayName = "Blademaster"),
	Champion		  = 25 UMETA(DisplayName = "Champion"),
	Druid			    = 26 UMETA(DisplayName = "Druid"),
	Eldritch		  = 27 UMETA(DisplayName = "Eldritch"),
	Enchanter		  = 28 UMETA(DisplayName = "Enchanter"),
	Hero			    = 29 UMETA(DisplayName = "Hero"),
	Mentalist		  = 30 UMETA(DisplayName = "Mentalist"),
	Nightshade		= 31 UMETA(DisplayName = "Nightshade"),
	Ranger			  = 32 UMETA(DisplayName = "Ranger"),
	Warden			  = 33 UMETA(DisplayName = "Warden"),
};

UENUM(BlueprintType)
enum class EProperty : uint8
{
	Undefined = 0,

	// Stats begin
	Stat_First = 1        UMETA(Hidden),
	Stat_Strength = 1     UMETA(DisplayName = "Stat_Strength"),
	Stat_Dexterity = 2    UMETA(DisplayName = "Stat_Dexterity"),
	Stat_Constitution = 3 UMETA(DisplayName = "Stat_Constitution"),
	Stat_Quickness = 4    UMETA(DisplayName = "Stat_Quickness"),
	Stat_Intelligence = 5 UMETA(DisplayName = "Stat_Intelligence"),
	Stat_Piety = 6        UMETA(DisplayName = "Stat_Piety"),
	Stat_Empathy = 7      UMETA(DisplayName = "Stat_Empathy"),
	Stat_Charisma = 8     UMETA(DisplayName = "Stat_Charisma"),
	Stat_last = 8         UMETA(Hidden),
	// Stats End

	MaxMana = 9           UMETA(DisplayName = "MaxMana"),
	MaxHealth = 10        UMETA(DisplayName = "MaxHealth"),

	// Resists begin
	Resist_First = 11     UMETA(Hidden),
	Resist_Body = 11      UMETA(DisplayName = "Resist_Body"),
	Resist_Cold = 12      UMETA(DisplayName = "Resist_Cold"),
	Resist_Crush = 13     UMETA(DisplayName = "Resist_Crush"),
	Resist_Energy = 14    UMETA(DisplayName = "Resist_Energy"),
	Resist_Heat = 15      UMETA(DisplayName = "Resist_Heat"),
	Resist_Matter = 16    UMETA(DisplayName = "Resist_Matter"),
	Resist_Slash = 17     UMETA(DisplayName = "Resist_Slash"),
	Resist_Spirit = 18    UMETA(DisplayName = "Resist_Spirit"),
	Resist_Thrust = 19    UMETA(DisplayName = "Resist_Thrust"),
	Resist_Last = 19      UMETA(Hidden),
	// Resists end

  // Specializations Begin
  Skill_First = 20              UMETA(Hidden),
  Skill_Two_Handed = 20,
  Skill_Body = 21,
  Skill_Chants = 22,
  Skill_Critical_Strike = 23,
  Skill_Cross_Bows = 24,
  Skill_Crushing = 25,
  Skill_Celtic_Dual = 26,
  Skill_Celtic_Spear = 27,
  Skill_Dual_Wield = 28,
  Skill_Earth = 29,
  Skill_Enhancement = 30,
  Skill_Envenom = 31,
  Skill_Fire = 32,
  Skill_RecurvedBow = 33,
  Skill_Cold = 34,
  Skill_Instruments = 35,
  Skill_Long_bows = 36,
  Skill_Matter = 37,
  Skill_Mind = 38,
  Skill_Music = 39,
  Skill_Parry = 40,
  Skill_Polearms = 41,
  Skill_Rejuvenation = 42,
  Skill_Shields = 43,
  Skill_Slashing = 44,
  Skill_Smiting = 45,
  Skill_SoulRending = 46,
  Skill_Spirit = 47,
  Skill_Staff = 48,
  Skill_Stealth = 49,
  Skill_Thrusting = 50,
  Skill_Wind = 51,
  Skill_Sword = 52,
  Skill_Hammer = 53,
  Skill_Axe = 54,
  Skill_Left_Axe = 55,
  Skill_Spear = 56,
  Skill_Mending = 57,
  Skill_Augmentation = 58,
  Skill_Cave_Magic = 59,
  Skill_Darkness = 60,
  Skill_Suppression = 61,
  Skill_Runecarving = 62,
  Skill_Stormcalling = 63,
  Skill_BeastCraft = 64,
  Skill_Light = 65,
  Skill_Void = 66,
  Skill_Mana = 67,
  Skill_Composite = 68,
  Skill_Battlesongs = 69,
  Skill_Enchantments = 70,
  Skill_Nature = 71,
  Skill_Blades = 72,
  Skill_Blunt = 73,
  Skill_Piercing = 74,
  Skill_Large_Weapon = 75,
  Skill_Mentalism = 76,
  Skill_Regrowth = 77,
  Skill_Nurture = 78,
  Skill_Last = 78                          UMETA(Hidden),
  // Specialization End

};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
  Undefined = 0                               UMETA(DisplayName = "Undefined"),
  Crush = (uint8)EProperty::Resist_Crush      UMETA(DisplayName = "Crush"),
  Slash = (uint8)EProperty::Resist_Slash      UMETA(DisplayName = "Slash"),
  Thrust = (uint8)EProperty::Resist_Thrust    UMETA(DisplayName = "Thrust"),
  Body = (uint8)EProperty::Resist_Body        UMETA(DisplayName = "Body"),
  Cold = (uint8)EProperty::Resist_Cold        UMETA(DisplayName = "Cold"),
  Energy = (uint8)EProperty::Resist_Energy    UMETA(DisplayName = "Energy"),
  Heat = (uint8)EProperty::Resist_Heat        UMETA(DisplayName = "Heat"),
  Matter = (uint8)EProperty::Resist_Matter    UMETA(DisplayName = "Matter"),
  Spirit = (uint8)EProperty::Resist_Spirit    UMETA(DisplayName = "Spirit")
};

UENUM(BlueprintType)
enum class EStat : uint8
{
	Undefined		  = 0                                   UMETA(DisplayName = "Undefined"),
	Strength		  = (uint8)EProperty::Stat_Strength     UMETA(DisplayName = "Strength"),
	Dexterity		  = (uint8)EProperty::Stat_Dexterity    UMETA(DisplayName = "Dexterity"),
	Constitution	= (uint8)EProperty::Stat_Constitution UMETA(DisplayName = "Constitution"),
	Quickness		  = (uint8)EProperty::Stat_Quickness    UMETA(DisplayName = "Quickness"),
	Intelligence	= (uint8)EProperty::Stat_Intelligence UMETA(DisplayName = "Intelligence"),
	Piety			    = (uint8)EProperty::Stat_Piety        UMETA(DisplayName = "Piety"),
	Empathy			  = (uint8)EProperty::Stat_Empathy      UMETA(DisplayName = "Empathy"),
	Charisma		  = (uint8)EProperty::Stat_Charisma     UMETA(DisplayName = "Charisma")
};

UENUM(BlueprintType)
enum class EResist : uint8
{
	Undefined	    = 0                                   UMETA(DisplayName = "Undefined"),
	Crush		      = (uint8)EProperty::Resist_Crush      UMETA(DisplayName = "Crush"),
	Slash		      = (uint8)EProperty::Resist_Slash      UMETA(DisplayName = "Slash"),
	Thrust		    = (uint8)EProperty::Resist_Thrust     UMETA(DisplayName = "Thrust"),
	Body		      = (uint8)EProperty::Resist_Body       UMETA(DisplayName = "Body"),
	Cold		      = (uint8)EProperty::Resist_Cold       UMETA(DisplayName = "Cold"),
	Energy		    = (uint8)EProperty::Resist_Energy     UMETA(DisplayName = "Energy"),
	Heat		      = (uint8)EProperty::Resist_Heat       UMETA(DisplayName = "Heat"),
	Matter		    = (uint8)EProperty::Resist_Matter     UMETA(DisplayName = "Matter"),
	Spirit		    = (uint8)EProperty::Resist_Spirit     UMETA(DisplayName = "Spirit")
};

UENUM(BlueprintType)
enum class ESkill : uint8
{
  Undefined       = 0                                             UMETA(DisplayName = "Undefined"),
  Two_Handed      = (uint8)EProperty::Skill_Two_Handed,
  Body            = (uint8)EProperty::Skill_Body,
  Chants          = (uint8)EProperty::Skill_Chants,
  Critical_Strike = (uint8)EProperty::Skill_Critical_Strike,
  Cross_Bows      = (uint8)EProperty::Skill_Cross_Bows,
  Crushing        = (uint8)EProperty::Skill_Crushing,
  Celtic_Dual     = (uint8)EProperty::Skill_Celtic_Dual,
  Celtic_Spear    = (uint8)EProperty::Skill_Celtic_Spear,
  Dual_Wield      = (uint8)EProperty::Skill_Dual_Wield,
  Earth           = (uint8)EProperty::Skill_Earth,
  Enhancement     = (uint8)EProperty::Skill_Enhancement,
  Envenom         = (uint8)EProperty::Skill_Envenom,
  Fire            = (uint8)EProperty::Skill_Fire,
  RecurvedBow     = (uint8)EProperty::Skill_RecurvedBow,
  Cold            = (uint8)EProperty::Skill_Cold ,
  Instruments     = (uint8)EProperty::Skill_Instruments,
  Long_bows       = (uint8)EProperty::Skill_Long_bows,
  Matter          = (uint8)EProperty::Skill_Matter,
  Mind            = (uint8)EProperty::Skill_Mind,
  Music           = (uint8)EProperty::Skill_Music,
  Parry           = (uint8)EProperty::Skill_Parry,
  Polearms        = (uint8)EProperty::Skill_Polearms,
  Rejuvenation    = (uint8)EProperty::Skill_Rejuvenation,
  Shields         = (uint8)EProperty::Skill_Shields,
  Slashing        = (uint8)EProperty::Skill_Slashing,
  Smiting         = (uint8)EProperty::Skill_Smiting,
  SoulRending     = (uint8)EProperty::Skill_SoulRending,
  Spirit          = (uint8)EProperty::Skill_Spirit,
  Staff           = (uint8)EProperty::Skill_Staff,
  Stealth         = (uint8)EProperty::Skill_Stealth,
  Thrusting       = (uint8)EProperty::Skill_Thrusting,
  Wind            = (uint8)EProperty::Skill_Wind,
  Sword           = (uint8)EProperty::Skill_Sword,
  Hammer          = (uint8)EProperty::Skill_Hammer,
  Axe             = (uint8)EProperty::Skill_Axe,
  Left_Axe        = (uint8)EProperty::Skill_Left_Axe,
  Spear           = (uint8)EProperty::Skill_Spear,
  Mending         = (uint8)EProperty::Skill_Mending,
  Augmentation    = (uint8)EProperty::Skill_Augmentation,
  Cave_Magic      = (uint8)EProperty::Skill_Cave_Magic,
  Darkness        = (uint8)EProperty::Skill_Darkness,
  Suppression     = (uint8)EProperty::Skill_Suppression,
  Runecarving     = (uint8)EProperty::Skill_Runecarving,
  Stormcalling    = (uint8)EProperty::Skill_Stormcalling,
  BeastCraft      = (uint8)EProperty::Skill_BeastCraft,
  Light           = (uint8)EProperty::Skill_Light,
  Void            = (uint8)EProperty::Skill_Void,
  Mana            = (uint8)EProperty::Skill_Mana,
  Composite       = (uint8)EProperty::Skill_Composite,
  Battlesongs     = (uint8)EProperty::Skill_Battlesongs,
  Enchantments    = (uint8)EProperty::Skill_Enchantments,
  Nature          = (uint8)EProperty::Skill_Nature,
  Blades          = (uint8)EProperty::Skill_Blades,
  Blunt           = (uint8)EProperty::Skill_Blunt,
  Piercing        = (uint8)EProperty::Skill_Piercing,
  Large_Weapon    = (uint8)EProperty::Skill_Large_Weapon,
  Mentalism       = (uint8)EProperty::Skill_Mentalism,
  Regrowth        = (uint8)EProperty::Skill_Regrowth,
  Nurture         = (uint8)EProperty::Skill_Nurture,
};

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	GenericItem       = 0  UMETA(DisplayName = "GenericItem"),
	GenericWeapon     = 1  UMETA(DisplayName = "GenericWeapon"),

	//Albion weapons
	_FirstWeapon      = 2  UMETA(Hidden),
	CrushingWeapon    = 2  UMETA(DisplayName = "CrushingWeapon"),
	SlashingWeapon    = 3  UMETA(DisplayName = "SlashingWeapon"),
	ThrustWeapon      = 4  UMETA(DisplayName = "ThrustWeapon"),
	Fired             = 5  UMETA(DisplayName = "Fired"),
	TwoHandedWeapon   = 6  UMETA(DisplayName = "TwoHandedWeapon"),
	PolearmWeapon     = 7  UMETA(DisplayName = "PolearmWeapon"),
	Staff             = 8  UMETA(DisplayName = "Staff"),
	Longbow           = 9  UMETA(DisplayName = "Longbow"),
	Crossbow          = 10 UMETA(DisplayName = "Crossbow"),

	//Midgard weapons
	Sword             = 11 UMETA(DisplayName = "Sword"),
	Hammer            = 12 UMETA(DisplayName = "Hammer"),
	Axe               = 13 UMETA(DisplayName = "Axe"),
	Spear             = 14 UMETA(DisplayName = "Spear"),
	CompositeBow      = 15 UMETA(DisplayName = "CompositeBow"),
	Thrown            = 16 UMETA(DisplayName = "Thrown"),
	LeftAxe           = 17 UMETA(DisplayName = "LeftAxe"),

	//Hibernia weapons
	RecurvedBow       = 18 UMETA(DisplayName = "RecurvedBow"),
	Blades            = 19 UMETA(DisplayName = "Blades"),
	Blunt             = 20 UMETA(DisplayName = "Blunt"),
	Piercing          = 21 UMETA(DisplayName = "Piercing"),
	LargeWeapons      = 22 UMETA(DisplayName = "LargeWeapons"),
	CelticSpear       = 23 UMETA(DisplayName = "CelticSpear"),
	_LastWeapon       = 23 UMETA(Hidden),

	//Armor
	_FirstArmor       = 24 UMETA(Hidden),
	GenericArmor      = 24 UMETA(DisplayName = "GenericArmor"),
	Cloth             = 25 UMETA(DisplayName = "Cloth"),
	Leather           = 26 UMETA(DisplayName = "Leather"),
	Studded           = 27 UMETA(DisplayName = "Studded"),
	Chain             = 28 UMETA(DisplayName = "Chain"),
	Plate             = 29 UMETA(DisplayName = "Plate"),
	Reinforced        = 30 UMETA(DisplayName = "Reinforced"),
	Scale             = 31 UMETA(DisplayName = "Scale"),
	_LastArmor        = 31 UMETA(Hidden),

	//Misc
  Consumable        = 32 UMETA(DisplayName = "Consumable"), // Consumable (Pots, food, etc) 
  Shield            = 33 UMETA(DisplayName = "Shield"),
  Arrow             = 34 UMETA(DisplayName = "Arrow"),
  Bolt              = 35 UMETA(DisplayName = "Bolt"),
  Instrument        = 36 UMETA(DisplayName = "Instrument"),
  Poison            = 37 UMETA(DisplayName = "Poison"),
  AlchemyTincture   = 38 UMETA(DisplayName = "AlchemyTincture"),
  SpellcraftGem     = 39 UMETA(DisplayName = "SpellcraftGem"),
  Currency          = 40 UMETA(DisplayName = "Currency"),
};

UENUM(BlueprintType)
enum class EClassType : uint8
{
  Undefined = 0 UMETA(DisplayName = "Undefined"),
  Caster    = 1 UMETA(DisplayName = "Caster"),
  Hybrid    = 2 UMETA(DisplayName = "Hybrid"),
  Tank      = 3 UMETA(DisplayName = "Tank")
};

UENUM(BlueprintType)
enum class EActiveWeaponSlot : uint8
{
  Standard  = 0 UMETA(DisplayName = "Standard"),
  TwoHanded = 1 UMETA(DisplayName = "TwoHanded"),
  Distance  = 2 UMETA(DisplayName = "Distance")
};

UENUM(BlueprintType)
enum class ETargetType : uint8
{
  Enemy = 0 UMETA(DisplayName = "Enemy"),
  Area = 1 UMETA(DisplayName = "Area"),
  Self = 2 UMETA(DisplayName = "Self"),
  Group = 3 UMETA(DisplayName = "Group"),
  Realm = 4 UMETA(DisplayName = "Realm"),
};

UENUM(BlueprintType)
enum class ESpellType : uint8
{
  Undefined = 0     UMETA(DisplayName = "Undefined"),
  DirectDamage = 1  UMETA(DisplayName = "DirectDamage"),
  AreaOfEffect = 2  UMETA(DisplayName = "AreaOfEffect"),
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
  Common = 0 UMETA(DisplayName = "Common"),
  Spells = 1 UMETA(DisplayName = "Spells"),
  Styles = 2 UMETA(DisplayName = "Styles"),
};


// Values Match Slots in UW_Equipment asset
UENUM(BlueprintType)
enum class EEquipmentSlots : uint8
{
  Chest = 0,
  Arms = 1,
  Jewellery = 2,
  LeftRing = 3,
  LeftBracer = 4,
  Legs = 5,
  Head = 6,
  Hands = 7,
  Waist = 8,
  RightRing = 9,
  RightBracer = 10,
  Feet = 11,
  Neck = 12,
  Cloak = 13,
  RightHandWeapon = 14,
  LeftHandWeapon = 15,
  TwoHandWeapon = 16,
  DistanceWeapon = 17,
  Count = 18
};


/**
 * 
 */
UCLASS()
class MMO_API UMMOGlobalConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
  static const FGameplayTag TagEquipmentSlotRightHandWeapon;
  static const FGameplayTag TagEquipmentSlotLeftHandWeapon;
  static const FGameplayTag TagEquipmentSlotTwoHandWeapon;
  static const FGameplayTag TagEquipmentSlotDistanceWeapon;
  static const FGameplayTag TagEquipmentSlotHead;
  static const FGameplayTag TagEquipmentSlotHands;
  static const FGameplayTag TagEquipmentSlotFeet;
  static const FGameplayTag TagEquipmentSlotJewellery;
  static const FGameplayTag TagEquipmentSlotChest;
  static const FGameplayTag TagEquipmentSlotCloak;
  static const FGameplayTag TagEquipmentSlotLegs;
  static const FGameplayTag TagEquipmentSlotArms;
  static const FGameplayTag TagEquipmentSlotNeck;
  static const FGameplayTag TagEquipmentSlotWaist;
  static const FGameplayTag TagEquipmentSlotLeftBracer;
  static const FGameplayTag TagEquipmentSlotRightBracer;
  static const FGameplayTag TagEquipmentSlotLeftRing;
  static const FGameplayTag TagEquipmentSlotRightRing;

  static FGameplayTag GetEquipmentTagForSlot(EEquipmentSlots EquipmentSlot);
  static bool IsWeaponSlot(EEquipmentSlots EquipmentSlot);


	UFUNCTION(BlueprintCallable, Category = "Globals")
	static TMap<EStat, int> GetStartingStatsForRace(ERace race);

	UFUNCTION(BlueprintCallable, Category = "Globals")
  static TArray<ECharacterClass> GetClassesForRealm(ERealm realm);

	UFUNCTION(BlueprintCallable, Category = "Globals")
  static TArray<ECharacterClass> GetClassesForRace(ERace race);

  UFUNCTION(BlueprintCallable, Category = "Globals")
  static bool IsCustomPointDistributionValid(ERace race, int level, TMap<EStat, int> stats);
};
