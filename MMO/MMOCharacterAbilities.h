// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMOCharacter.h"
#include "AbilitySystemInterface.h" 
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "MMOAttributeSet.h"
#include "MMOUI/MMOInventoryTypes.h"
#include "MMOInterfaces/MMOCharacterAbilitiesInterface.h"
#include "MMOInventory/MMOEquipmentInventoryComponent.h"
#include "MMOCharacterAbilities.generated.h"



UENUM(BlueprintType)
enum class AbilityInput : uint8
{
  UseInputNone UMETA(DisplayName = "None"), //This maps the first ability(input ID should be 0 in int) to the action mapping(which you define in the project settings) by the name of "UseAbility1". "Use Spell 1" is the blueprint name of the element.
  UseAbility2 UMETA(DisplayName = "Use Ability 2"),
  UseAbility3 UMETA(DisplayName = "Use Ability 3"),
  UseAbility4 UMETA(DisplayName = "Use Ability 4"),
  UseWeapon1 UMETA(DisplayName = "Use Weapon 1"),
  UseWeapon2 UMETA(DisplayName = "Use Weapon 2"),
  UseAbility_Stealth UMETA(DisplayName = "Use Ability Stealth"),
};


/**
 * 
 */
UCLASS(abstract, BlueprintType, hidecategories = (CharacterStats, Health))
class MMO_API AMMOCharacterAbilities : public AMMOCharacter, public IAbilitySystemInterface, public IMMOCharacterAbilitiesInterface
{
	GENERATED_BODY()
	
public:
  // Sets default values for this character's properties
  AMMOCharacterAbilities(const class FObjectInitializer& ObjectInitializer);

  static FName AbilitySystemComponentName;

  virtual void BeginPlay() override;
  virtual void PostInitializeComponents() override;
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
  virtual void PossessedBy(AController* NewController) override;
  virtual void OnRep_Controller() override;

  void AddDefaultGameplayAbilities();
  void SetupAttributeChangeDelegates();
  
  // --- Equipment ---

  // Chest
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* ChestMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ChestMesh, Category = "Equipment")
  USkeletalMesh* ChestMesh;
  UFUNCTION()
  void OnRep_ChestMesh();

  // Arms
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* ArmsMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ArmsMesh, Category = "Equipment")
  USkeletalMesh* ArmsMesh;
  UFUNCTION()
  void OnRep_ArmsMesh();

  // Hands
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* HandsMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HandsMesh, Category = "Equipment")
  USkeletalMesh* HandsMesh;
  UFUNCTION()
  void OnRep_HandsMesh();

  // Legs
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* LegsMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LegsMesh, Category = "Equipment")
  USkeletalMesh* LegsMesh;
  UFUNCTION()
  void OnRep_LegsMesh();

  // Feet
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* FeetMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FeetMesh, Category = "Equipment")
  USkeletalMesh* FeetMesh;
  UFUNCTION()
  void OnRep_FeetMesh();

  // Cloak
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* CloakMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CloakMesh, Category = "Equipment")
  USkeletalMesh* CloakMesh;
  UFUNCTION()
  void OnRep_CloakMesh();

  // --- Socket Based ---

  // Helm
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* HelmMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HelmMesh, Category = "Equipment")
  USkeletalMesh* HelmMesh;
  UFUNCTION()
  void OnRep_HelmMesh();

  // Right Hand
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* RightHandMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RightHandMesh, Category = "Equipment")
  USkeletalMesh* RightHandMesh;
  UFUNCTION()
  void OnRep_RightHandMesh();

  // Left Hand
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* LeftHandMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LeftHandMesh, Category = "Equipment")
  USkeletalMesh* LeftHandMesh;
  UFUNCTION()
  void OnRep_LeftHandMesh();

  // Shield Hand
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* ShieldHandMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ShieldHandMesh, Category = "Equipment")
  USkeletalMesh* ShieldHandMesh;
  UFUNCTION()
  void OnRep_ShieldHandMesh();

  // RightHandSheath
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* RightHandSheathMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RightHandSheathMesh, Category = "Equipment")
  USkeletalMesh* RightHandSheathMesh;
  UFUNCTION()
  void OnRep_RightHandSheathMesh();

  // LeftHandSheath
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* LeftHandSheathMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LeftHandSheathMesh, Category = "Equipment")
  USkeletalMesh* LeftHandSheathMesh;
  UFUNCTION()
  void OnRep_LeftHandSheathMesh();

  // TwoHandSheath
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* TwoHandSheathMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_TwoHandSheathMesh, Category = "Equipment")
  USkeletalMesh* TwoHandSheathMesh;
  UFUNCTION()
  void OnRep_TwoHandSheathMesh();

  // RangedSheath
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  USkeletalMeshComponent* RangedSheathMeshComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RangedSheathMesh, Category = "Equipment")
  USkeletalMesh* RangedSheathMesh;
  UFUNCTION()
  void OnRep_RangedSheathMesh();


  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  class UMMOActorWidgetComponent* NamePlate;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  class UBoxComponent* MeleeHitBox;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UMMOEquipmentInventoryComponent* EquipmentComponent;

  // --- MMOCharacterAbilitiesInterface ---
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Interface")
  class USoundCue* FootStepSound = nullptr;

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character Interface")
  void OnFootStep(bool LeftFoot);



  // Equipment
  UFUNCTION(BlueprintCallable, Category = "Equipment")
  void UpdateEquippedMeshes(const FInventoryItem& Item, bool Unequip, const FGameplayTag& UnequipSlot);


  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
  FInventoryItem ItemToEquip;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
  FGameplayTag SlotToUnEquip;

  UFUNCTION(BlueprintCallable, Category = "Equipment")
  void Equip(const FInventoryItem& Item);

  UFUNCTION(BlueprintCallable, Category = "Equipment")
  void Unequip(const FGameplayTag& Slot, bool UpdateMeshes);



  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_IsStealthed, Category = "Combat")
  bool IsStealthed = false;
  UFUNCTION()
  void OnRep_IsStealthed();

  // --- Combat ---
  UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
  EActiveWeaponSlot ActiveWeaponSlot;

  UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
  bool AttackState = false;

  FTimerHandle AttackTimerHandle;

  UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation, Category = "Combat")
  void Server_ToggleAttackState();

  UFUNCTION(BlueprintCallable, Category = "Combat")
  virtual void StartAttacking(AMMOCharacterAbilities* AttackTarget);

  virtual void OnTickAttack();

  UFUNCTION(BlueprintCallable, Category = "Combat")
  virtual void StopAttacking();

  void SheathWeapons(bool Unsheath);

  UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation, Category = "Combat")
  void Server_SwitchActiveWeapon(EActiveWeaponSlot NewActiveWeapon);

  UFUNCTION(BlueprintCallable, Category = "Combat")
  void SwitchActiveWeapon(EActiveWeaponSlot NewActiveWeapon);


  UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
  AActor* TargetObject;


  UFUNCTION()
  void OnGameplayEffectTagCountChanged(const FGameplayTag GameplayTag, int32 TagCount);

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
  class UAbilitySystemComponent* AbilitySystem;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
  UMMOAttributeSet* AttributeSet;

  UAbilitySystemComponent* GetAbilitySystemComponent() const override
  {
    return AbilitySystem;
  };


  virtual void OnAttacked(AMMOCharacterAbilities* Attacker);

  virtual void Die(AMMOCharacterAbilities* Killer);

  UFUNCTION(NetMulticast, Reliable, WithValidation)
  void Multicast_Die();

  UFUNCTION(NetMulticast, Reliable, BlueprintCallable, WithValidation)
  void Multicast_Respawn();

  UFUNCTION(NetMulticast, Reliable, BlueprintCallable, WithValidation)
  void Multicast_SpawnEmitterAttached(class UParticleSystem* EmitterTemplate, FName AttachPointName = NAME_None, FVector Location = FVector(ForceInit), FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1.f), EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset, bool bAutoDestroy = true, EPSCPoolMethod PoolingMethod = EPSCPoolMethod::None, bool bAutoActivate = true);


  virtual void GainExperience(int32 XPAmount);


  UFUNCTION(BlueprintImplementableEvent, Category = Combat)
  void OnDeath(AMMOCharacter* WhoKilledMe);
  UFUNCTION(BlueprintImplementableEvent, Category = Combat)
  void OnTakeDamage(AMMOCharacter* WhoAttackedMe, float DamageAmount, bool IsCritical);
  UFUNCTION(BlueprintImplementableEvent, Category = Combat)
  void OnInflictDamage(AMMOCharacter* WhoWasDamaged, float DamageAmount, bool IsCritical);
  UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
  void CalculateUpdatedDamage(float OriginalDamage, const UMMOAttributeSet* SourceAttributes, FGameplayTagContainer EffectTags, float& NewDamage, bool& IsCritical);


  // Health Change
  void OnHealthChange(const FOnAttributeChangeData& Data);
  UFUNCTION(BlueprintImplementableEvent)
  void HealthChanged(float OldValue, float NewValue);

  // Energy Change
  void OnEnduranceChange(const FOnAttributeChangeData& Data);
  UFUNCTION(BlueprintImplementableEvent)
  void EnduranceChanged(float OldValue, float NewValue);

  // Mana Change
  void OnManaChange(const FOnAttributeChangeData& Data);
  UFUNCTION(BlueprintImplementableEvent)
  void ManaChanged(float OldValue, float NewValue);

  // --- Load and Get Character Data ---

  virtual void LoadCharacterData() override;
  virtual void LoadAttributeSetFromJSON(TSharedPtr<FJsonObject> JsonObject);


  UFUNCTION(BlueprintCallable, Category = "Attributes")
  void SetAttributeBaseStat(EStat Stat, float Value);

  UFUNCTION(BlueprintCallable, Category = "Attributes")
  void SetAttributeBaseResist(EResist Resist, float Value);


  //Get Character Stats
  UFUNCTION(BlueprintCallable, Category = "Stats")
  void GetCharacterData();

  void OnGetCharacterDataResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
  UFUNCTION(BlueprintImplementableEvent, Category = "Init")
  void OnMMOLoadCharacterDataComplete();


  UFUNCTION(BlueprintCallable, Category = Combat)
  void GrantAbility(TSubclassOf<class UGameplayAbility> NewAbility, int32 AbilityLevel, AbilityInput InputID);

  UFUNCTION(BlueprintCallable, Category = Combat)
  void ActivateAbility(AbilityInput InputID);
  UFUNCTION(BlueprintCallable, Category = Combat)
  void DeactivateAbility(AbilityInput InputID);

  UFUNCTION(BlueprintCallable, Category = "Abilities")
  bool ActivateAbilityByClass(TSubclassOf<UGameplayAbility> InAbilityToActivate, bool bAllowRemoteActivation = true );
  
  // Effects
  TArray<FActiveGameplayEffectHandle> EffectHandles;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayEffect> Effect1;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayEffect> Effect2;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayEffect> Effect3;

  // Abilities
  UPROPERTY()
  TArray<FGameplayAbilitySpecHandle> AbilityHandles;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> EquipAbility;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> UnequipAbility;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> AttackAbility;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> CastInterruptAbility;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> DeathAbility;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> RespawnAbility;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> Ability1;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> Ability2;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> Ability3;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> Ability4;
  
  // Weapons
  UPROPERTY()
  TArray<FGameplayAbilitySpecHandle> WeaponAbilityHandles;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> Weapon1;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
  TSubclassOf<UGameplayAbility> Weapon2;
};
