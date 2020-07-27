// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOCharacterAbilities.h"
#include "MMOPlayerController.h"
#include "MMOPlayerState.h"
#include "MMOUI/MMOActorWidgetComponent.h"
#include "MMOInterfaces/MMOCharacterAnimationInterface.h"
#include <GameFramework/Controller.h>
#include <GameFramework/Character.h>
#include <GameFramework/Actor.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SceneComponent.h>
#include <Components/BoxComponent.h>
#include <Net/UnrealNetwork.h>
#include <GameplayTagsManager.h>
#include <GameplayTagsModule.h>
#include <TimerManager.h>

#define CONSTRUCT_CLASS(Class, Name) Class* Name = NewObject<Class>(GetTransientPackage(), FName(TEXT(#Name)))
FName AMMOCharacterAbilities::AbilitySystemComponentName(TEXT("AbilitySystem"));

AMMOCharacterAbilities::AMMOCharacterAbilities(const class FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
  AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(AMMOCharacterAbilities::AbilitySystemComponentName);
  AbilitySystem->SetIsReplicated(true);

  AbilityHandles.SetNum(10, false);
  WeaponAbilityHandles.SetNum(4, false);
  EffectHandles.SetNum(3, false);

  AttributeSet = CreateDefaultSubobject<UMMOAttributeSet>(TEXT("AttributeSet"));

  NamePlate = CreateDefaultSubobject<UMMOActorWidgetComponent>(TEXT("NamePlate"));
  NamePlate->SetupAttachment(GetRootComponent());

  MeleeHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeHitBox"));
  MeleeHitBox->SetBoxExtent(FVector(32.0F));
  MeleeHitBox->SetupAttachment(GetRootComponent());

  EquipmentComponent = CreateDefaultSubobject<UMMOEquipmentInventoryComponent>("EquipmentComponent");


  // Equipment
  ChestMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("ChestMeshComponent");
  if (ChestMeshComponent)
  {
    ChestMeshComponent->SetupAttachment(GetMesh());
  }

  ArmsMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("ArmsMeshComponent");
  if (ArmsMeshComponent)
  {
    ArmsMeshComponent->SetupAttachment(GetMesh());
  }

  HandsMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("HandsMeshComponent");
  if (HandsMeshComponent)
  {
    HandsMeshComponent->SetupAttachment(GetMesh());
  }
  
  LegsMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("LegsMeshComponent");
  if (LegsMeshComponent)
  {
    LegsMeshComponent->SetupAttachment(GetMesh());
  }

  FeetMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("FeetMeshComponent");
  if (FeetMeshComponent)
  {
    FeetMeshComponent->SetupAttachment(GetMesh());
  }

  CloakMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("CloakMeshComponent");
  if (CloakMeshComponent)
  {
    CloakMeshComponent->SetupAttachment(GetMesh());
  }

  HelmMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("HelmMeshComponent");
  if (HelmMeshComponent)
  {
    HelmMeshComponent->SetupAttachment(GetMesh());
  }

  RightHandMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("RightHandMeshComponent");
  if (RightHandMeshComponent)
  {
    RightHandMeshComponent->SetupAttachment(GetMesh());
  }

  LeftHandMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("LeftHandMeshComponent");
  if (LeftHandMeshComponent)
  {
    LeftHandMeshComponent->SetupAttachment(GetMesh());
  }

  ShieldHandMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("ShieldHandMeshComponent");
  if (ShieldHandMeshComponent)
  {
    ShieldHandMeshComponent->SetupAttachment(GetMesh());
  }

  RightHandSheathMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("RightHandSheathMeshComponent");
  if (RightHandSheathMeshComponent)
  {
    RightHandSheathMeshComponent->SetupAttachment(GetMesh());
  }

  LeftHandSheathMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("LeftHandSheathMeshComponent");
  if (LeftHandSheathMeshComponent)
  {
    LeftHandSheathMeshComponent->SetupAttachment(GetMesh());
  }

  TwoHandSheathMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("TwoHandSheathMeshComponent");
  if (TwoHandSheathMeshComponent)
  {
    TwoHandSheathMeshComponent->SetupAttachment(GetMesh());
  }

  RangedSheathMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("RangedSheathMeshComponent");
  if (RangedSheathMeshComponent)
  {
    RangedSheathMeshComponent->SetupAttachment(GetMesh());
  }
}

void AMMOCharacterAbilities::BeginPlay()
{
  Super::BeginPlay();

  //MMOAttributes = NewObject<UMMOAttributeSet>();

  if (HasAuthority())
  {
    // Call 
    if (IsAMob)
    {
      OnMMOLoadCharacterDataComplete();
    }
  }

  SetupAttributeChangeDelegates();
}

void AMMOCharacterAbilities::PostInitializeComponents()
{
  Super::PostInitializeComponents();
}

void AMMOCharacterAbilities::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
  AbilitySystem->RegisterGenericGameplayTagEvent().AddUObject(this, &AMMOCharacterAbilities::OnGameplayEffectTagCountChanged);
}

void AMMOCharacterAbilities::PossessedBy(AController* NewController)
{
  Super::PossessedBy(NewController);


  //Initialize our abilities
  if (AbilitySystem)
  {
    AbilitySystem->InitAbilityActorInfo(this, this);
    AddDefaultGameplayAbilities();
  }
}

void AMMOCharacterAbilities::LoadCharacterData()
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: LoadCharacterData"));
  GetCharacterData();
}

void AMMOCharacterAbilities::LoadAttributeSetFromJSON(TSharedPtr<FJsonObject> JsonObject)
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: LoadAttributeSetFromJSON"));

  // Player Stats
  static UProperty* StrengthProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Strength));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(StrengthProperty), JsonObject->GetNumberField("Strength"));
  static UProperty* DexterityProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Dexterity));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(DexterityProperty), JsonObject->GetNumberField("Dexterity"));
  static UProperty* ConstitutionProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Constitution));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(ConstitutionProperty), JsonObject->GetNumberField("Constitution"));
  static UProperty* QuicknessProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Quickness));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(QuicknessProperty), JsonObject->GetNumberField("Quickness"));
  static UProperty* IntelligenceProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Intelligence));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(IntelligenceProperty), JsonObject->GetNumberField("Intelligence"));
  static UProperty* PietyProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Piety));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(PietyProperty), JsonObject->GetNumberField("Piety"));
  static UProperty* EmpathyProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Empathy));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(EmpathyProperty), JsonObject->GetNumberField("Empathy"));
  static UProperty* CharismaProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Charisma));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(CharismaProperty), JsonObject->GetNumberField("Charisma"));


  // GamePlayer: CalculateMaxHealth -> ICharacterClass Base HP

  static UProperty* MaxHealthProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, MaxHealth));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(MaxHealthProperty), 130.0f);
  static UProperty* HealthProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Health));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(HealthProperty), 90.0f);
  static UProperty* HealthRegenRateProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, HealthRegenRate));
  GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(HealthRegenRateProperty), 1.0f);


  TMap<EStat, int> StartingStats = UMMOGlobalConstants::GetStartingStatsForRace((ERace) Race);
  for (TMap<EStat, int>::TIterator it = StartingStats.CreateIterator(); it; ++it)
  {
    SetAttributeBaseStat(it->Key, it->Value);
  }
}

void AMMOCharacterAbilities::SetAttributeBaseStat(EStat Stat, float Value)
{
  switch (Stat)
  {
  case EStat::Strength:
    static UProperty* StrengthProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Strength));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(StrengthProperty), Value);
    Strength = Value;
    break;
  case EStat::Dexterity:
    static UProperty* DexterityProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Dexterity));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(DexterityProperty), Value);
    Dexterity = Value;
    break;
  case EStat::Constitution:
    static UProperty* ConstitutionProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Constitution));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(ConstitutionProperty), Value);
    Constitution = Value;
    break;
  case EStat::Quickness:
    static UProperty* QuicknessProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Quickness));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(QuicknessProperty), Value);
    Quickness = Value;
    break;
  case EStat::Intelligence:
    static UProperty* IntelligenceProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Intelligence));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(IntelligenceProperty), Value);
    Intelligence = Value;
    break;
  case EStat::Piety:
    static UProperty* PietyProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Piety));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(PietyProperty), Value);
    Piety = Value;
    break;
  case EStat::Empathy:
    static UProperty* EmpathyProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Empathy));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(EmpathyProperty), Value);
    Empathy = Value;
    break;
  case EStat::Charisma:
    static UProperty* CharismaProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, Charisma));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(CharismaProperty), Value);
    Charisma = Value;
    break;
    // Log warning
  case EStat::Undefined:
  default:
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities::SetAttributeBaseStat - Stat is undefined"));
    break;
  }
}


void AMMOCharacterAbilities::SetAttributeBaseResist(EResist Resist, float Value)
{
  switch (Resist)
  {
  case EResist::Crush:
    static UProperty* CrushProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, CrushResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(CrushProperty), Value);
    CrushResist = Value;
    break;
  case EResist::Slash:
    static UProperty* SlashProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, SlashResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(SlashProperty), Value);
    SlashResist = Value;
    break;
  case EResist::Thrust:
    static UProperty* ThrustProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, ThrustResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(ThrustProperty), Value);
    ThrustResist = Value;
    break;
  case EResist::Body:
    static UProperty* BodyProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, BodyResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(BodyProperty), Value);
    BodyResist = Value;
    break;
  case EResist::Cold:
    static UProperty* ColdProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, ColdResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(ColdProperty), Value);
    ColdResist = Value;
    break;
  case EResist::Energy:
    static UProperty* EnergyProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, EnergyResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(EnergyProperty), Value);
    EnergyResist = Value;
    break;
  case EResist::Heat:
    static UProperty* HeatProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, HeatResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(HeatProperty), Value);
    HeatResist = Value;
    break;
  case EResist::Matter:
    static UProperty* MatterProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, MatterResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(MatterProperty), Value);
    MatterResist = Value;
    break;
  case EResist::Spirit:
    static UProperty* SpiritProperty = FindFieldChecked<UProperty>(UMMOAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMMOAttributeSet, SpiritResist));
    GetAbilitySystemComponent()->SetNumericAttributeBase(FGameplayAttribute(SpiritProperty), Value);
    SpiritResist = Value;
    break;
  case EResist::Undefined:
  default:
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities::SetAttributeBaseResist - Resist is undefined"));
    break;

  }
}

void AMMOCharacterAbilities::GetCharacterData()
{
  AMMOPlayerController* PC = Cast<AMMOPlayerController>(this->Controller);
  if (PC && PC->PlayerState)
  {
    FString PlayerName = PC->PlayerState->GetPlayerName();
    PlayerName = PlayerName.Replace(TEXT(" "), TEXT("%20"));


    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: GetCharacterData Player Name :%s"), *PlayerName);

    Http = &FHttpModule::Get();

    TSharedRef<IHttpRequest> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AMMOCharacterAbilities::OnGetCharacterDataResponseReceived);
    //This is the url on which to process the request
    FString url = FString(TEXT("http://" + WebApiPath + "/character/GetCharacter?characterName=" + PlayerName));

    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: RequestURL :%s"), *url);

    Request->SetURL(url);
    Request->SetVerb("GET");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));
    Request->SetContentAsString("");
    Request->ProcessRequest();
  }
}

void AMMOCharacterAbilities::OnGetCharacterDataResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
  if (bWasSuccessful)
  {
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
      LoadCharacterDataFromJSON(JsonObject);
      LoadAttributeSetFromJSON(JsonObject);

      OnMMOLoadCharacterDataComplete();
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("OnGetCharacterDataResponseReceived Server returned no data!"));
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("OnGetCharacterDataResponseReceived Error accessing server!"));
  }
}

void AMMOCharacterAbilities::OnRep_Controller()
{
  Super::OnRep_Controller();

  // Our controller changed, must update ActorInfo on AbilitySystemComponent
  if (AbilitySystem)
  {
    AbilitySystem->RefreshAbilityActorInfo();
  }
}

void AMMOCharacterAbilities::AddDefaultGameplayAbilities()
{
  if (AbilitySystem && HasAuthority())
  {

    FGameplayEffectContextHandle effectContextHandle = AbilitySystem->MakeEffectContext();
    if (Effect1)
    {
      EffectHandles[0] = AbilitySystem->ApplyGameplayEffectToSelf(Effect1.GetDefaultObject(), 1, effectContextHandle);
      UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities::ApplyGameplayEffect1"));
    }

    if (Effect2)
    {
      EffectHandles[1] = AbilitySystem->ApplyGameplayEffectToSelf(Effect2.GetDefaultObject(), 1, effectContextHandle);
      UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities::ApplyGameplayEffect2"));
    }

    if (Effect3)
    {
      EffectHandles[2] = AbilitySystem->ApplyGameplayEffectToSelf(Effect3.GetDefaultObject(), 1, effectContextHandle);
      UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities::ApplyGameplayEffect3"));
    }
    // Common



    // Spells
    if (Ability1)
    {
      AbilityHandles[0] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability1.GetDefaultObject(), 1, 0));
    }

    if (Ability2)
    {
      AbilityHandles[1] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability2.GetDefaultObject(), 1, 1));
    }

    if (Ability3)
    {
      AbilityHandles[2] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability3.GetDefaultObject(), 1, 2));
    }

    if (Ability4)
    {
      AbilityHandles[3] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability4.GetDefaultObject(), 1, 3));
    }


    if (EquipAbility)
    {
      AbilityHandles[4] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(EquipAbility.GetDefaultObject(), 1));
    }

    if (UnequipAbility)
    {
      AbilityHandles[5] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(UnequipAbility.GetDefaultObject(), 1));
    }

    if (AttackAbility)
    {
      AbilityHandles[6] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(AttackAbility.GetDefaultObject(), 1));
    }

    if (CastInterruptAbility)
    {
      AbilityHandles[7] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(CastInterruptAbility.GetDefaultObject(), 1));
    }

    if (DeathAbility)
    {
      AbilityHandles[8] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(DeathAbility.GetDefaultObject(), 1));
    }

    if (RespawnAbility)
    {
      AbilityHandles[9] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(RespawnAbility.GetDefaultObject(), 1));
    }

    


    // Weapons
    if (Weapon1)
    {
      WeaponAbilityHandles[0] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Weapon1.GetDefaultObject(), 1, 4));
    }

    if (Weapon2)
    {
      WeaponAbilityHandles[1] = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Weapon2.GetDefaultObject(), 1, 5));
    }

  }
}

void AMMOCharacterAbilities::SetupAttributeChangeDelegates()
{
  if (AbilitySystem)
  {
    AbilitySystem->GetGameplayAttributeValueChangeDelegate(UMMOAttributeSet::GetHealthAttribute()).AddUObject(this, &AMMOCharacterAbilities::OnHealthChange);
    AbilitySystem->GetGameplayAttributeValueChangeDelegate(UMMOAttributeSet::GetEnduranceAttribute()).AddUObject(this, &AMMOCharacterAbilities::OnEnduranceChange);
    AbilitySystem->GetGameplayAttributeValueChangeDelegate(UMMOAttributeSet::GetManaAttribute()).AddUObject(this, &AMMOCharacterAbilities::OnManaChange);
  }
}

void AMMOCharacterAbilities::OnRep_ChestMesh()
{
  if (ChestMeshComponent)
  {
    ChestMeshComponent->SetSkeletalMesh(ChestMesh, true);
    ChestMeshComponent->SetMasterPoseComponent(GetMesh(), false);
  }
}

void AMMOCharacterAbilities::OnRep_ArmsMesh()
{
  if (ArmsMeshComponent)
  {
    ArmsMeshComponent->SetSkeletalMesh(ArmsMesh, true);
    ArmsMeshComponent->SetMasterPoseComponent(GetMesh(), false);
  }
}

void AMMOCharacterAbilities::OnRep_HandsMesh()
{
  if (HandsMeshComponent)
  {
    HandsMeshComponent->SetSkeletalMesh(HandsMesh, true);
    HandsMeshComponent->SetMasterPoseComponent(GetMesh(), false);
  }
}

void AMMOCharacterAbilities::OnRep_LegsMesh()
{
  if (LegsMeshComponent)
  {
    LegsMeshComponent->SetSkeletalMesh(LegsMesh, true);
    LegsMeshComponent->SetMasterPoseComponent(GetMesh(), false);
  }
}

void AMMOCharacterAbilities::OnRep_FeetMesh()
{
  if (FeetMeshComponent)
  {
    FeetMeshComponent->SetSkeletalMesh(FeetMesh, true);
    FeetMeshComponent->SetMasterPoseComponent(GetMesh(), false);
  }
}

void AMMOCharacterAbilities::OnRep_CloakMesh()
{
  if (CloakMeshComponent)
  {
    CloakMeshComponent->SetSkeletalMesh(CloakMesh, true);
    CloakMeshComponent->SetMasterPoseComponent(GetMesh(), false);
  }
}

void AMMOCharacterAbilities::OnRep_HelmMesh()
{
  if (HelmMeshComponent)
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: OnRep_HelmMesh"));
    HelmMeshComponent->SetSkeletalMesh(HelmMesh, true);
    HelmMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "HelmSocket");
  }
}

void AMMOCharacterAbilities::OnRep_RightHandMesh()
{
  if (RightHandMeshComponent)
  {
    RightHandMeshComponent->SetSkeletalMesh(RightHandMesh, true);
    RightHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "RightHandSocket");
  }
}

void AMMOCharacterAbilities::OnRep_LeftHandMesh()
{
  if (LeftHandMeshComponent)
  {
    LeftHandMeshComponent->SetSkeletalMesh(LeftHandMesh, true);
    LeftHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "LeftHandSocket");
  }
}

void AMMOCharacterAbilities::OnRep_ShieldHandMesh()
{
  if (ShieldHandMeshComponent)
  {
    ShieldHandMeshComponent->SetSkeletalMesh(ShieldHandMesh, true);
    ShieldHandMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "ShieldSocket");
  }
}

void AMMOCharacterAbilities::OnRep_RightHandSheathMesh()
{
  if (RightHandSheathMeshComponent)
  {
    RightHandSheathMeshComponent->SetSkeletalMesh(RightHandSheathMesh, true);
    RightHandSheathMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "RightHandSheathSocket");
  }
}

void AMMOCharacterAbilities::OnRep_LeftHandSheathMesh()
{
  if (LeftHandSheathMeshComponent)
  {
    LeftHandSheathMeshComponent->SetSkeletalMesh(LeftHandSheathMesh, true);
    LeftHandSheathMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "LeftHandSheathSocket");
  }
}

void AMMOCharacterAbilities::OnRep_TwoHandSheathMesh()
{
  if (TwoHandSheathMeshComponent)
  {
    TwoHandSheathMeshComponent->SetSkeletalMesh(TwoHandSheathMesh, true);
    TwoHandSheathMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "TwoHandSheathSocket");
  }
}

void AMMOCharacterAbilities::OnRep_RangedSheathMesh()
{
  if (RangedSheathMeshComponent)
  {
    RangedSheathMeshComponent->SetSkeletalMesh(RangedSheathMesh, true);
    RangedSheathMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "RangedSheathSocket");
  }
}

void AMMOCharacterAbilities::OnFootStep_Implementation(bool LeftFoot)
{
  if (!HasAuthority())
  {
    if (FootStepSound)
    {
      UGameplayStatics::PlaySoundAtLocation(this, (USoundBase*)FootStepSound, GetActorLocation());
    }
  }
}

void AMMOCharacterAbilities::UpdateEquippedMeshes(const FInventoryItem& Item, bool Unequip, const FGameplayTag& UnequipSlot)
{
  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: UpdateEquippedMeshes called on client"));
    return;
  }


  const FGameplayTag& SlotTag = Unequip ? UnequipSlot : Item.EquipmentSlot;
  USkeletalMesh* EquipMesh    = Unequip ? nullptr     : Item.EquipmentMesh;


  if (SlotTag.MatchesTagExact(UMMOGlobalConstants::TagEquipmentSlotRightHandWeapon))
  {
    RightHandSheathMesh = EquipMesh;

    //SwitchActiveWeapon(EActiveWeaponSlot::Standard);

    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: RightHandWeaponTag Match!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
  }
  else if (SlotTag.MatchesTagExact(UMMOGlobalConstants::TagEquipmentSlotLeftHandWeapon))
  {
    if (Unequip)
    {
      ShieldHandMesh      = nullptr;
      LeftHandSheathMesh  = nullptr;
    }
    else if (Item.ItemType == EObjectType::Shield)
    {
      ShieldHandMesh      = EquipMesh;
      LeftHandSheathMesh  = nullptr;
    }
    else
    {
      LeftHandSheathMesh  = EquipMesh;
      ShieldHandMesh      = nullptr;
    }

    //SwitchActiveWeapon(EActiveWeaponSlot::Standard);

    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: LeftHandWeaponTag Match!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
  }
  else if (SlotTag.MatchesTagExact(UMMOGlobalConstants::TagEquipmentSlotTwoHandWeapon))
  {
    TwoHandSheathMesh     = EquipMesh;
    ShieldHandMesh        = nullptr;

    //SwitchActiveWeapon(EActiveWeaponSlot::TwoHanded);

    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: TwoHandWeaponTag Match!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
  }
  else if (SlotTag.MatchesTagExact(UMMOGlobalConstants::TagEquipmentSlotDistanceWeapon))
  {
    RangedSheathMesh      = EquipMesh;
    ShieldHandMesh        = nullptr;

    //SwitchActiveWeapon(EActiveWeaponSlot::Distance);

    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: DistanceWeaponTag Match!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
  }
  else if (SlotTag.MatchesTagExact(UMMOGlobalConstants::TagEquipmentSlotHead))
  {
    HelmMesh = EquipMesh;

    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: HeadTag Match!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
  }
}

void AMMOCharacterAbilities::Equip(const FInventoryItem& Item)
{
  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: Equip called on client"));
    return;
  }

  StopAttacking();

  ItemToEquip = Item;

  if (EquipAbility)
  {
    AbilitySystem->TryActivateAbilityByClass(EquipAbility);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: Equip - EquipAbility not valid"));
  }

  UpdateEquippedMeshes(Item, false, FGameplayTag());
}

void AMMOCharacterAbilities::Unequip(const FGameplayTag& Slot, bool UpdateMeshes)
{
  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: Unequip called on client"));
    return;
  }

  StopAttacking();

  SlotToUnEquip = Slot;

  if (UnequipAbility)
  {
    AbilitySystem->TryActivateAbilityByClass(UnequipAbility);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: Unequip - UnequipAbility not valid"));
  }

  if (UpdateMeshes)
  {
    UpdateEquippedMeshes(FInventoryItem(), true, SlotToUnEquip);
  }

}

void AMMOCharacterAbilities::OnRep_IsStealthed()
{
  UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

  if (AnimInstance)
  {
    IMMOCharacterAnimationInterface* AnimInterface = Cast<IMMOCharacterAnimationInterface>(AnimInstance);

    if (AnimInterface)
    {
      AnimInterface->Execute_OnToggleStealthAnimation(AnimInstance, IsStealthed);
    }
  }
}

void AMMOCharacterAbilities::Server_ToggleAttackState_Implementation()
{
  if (AttackState)
  {
    StopAttacking();
  }
  else
  {
    AMMOCharacterAbilities* AttackTarget = Cast<AMMOCharacterAbilities>(TargetObject);
    if (AttackTarget)
    {
      StartAttacking(AttackTarget);
    }
  }
}

bool AMMOCharacterAbilities::Server_ToggleAttackState_Validate()
{
  return true;
}

void AMMOCharacterAbilities::StartAttacking(AMMOCharacterAbilities* AttackTarget)
{
  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: StartAttacking called on client"));
    return;
  }


  if (AttackState == true) return;

  AttackState = true;

  GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AMMOCharacterAbilities::OnTickAttack, 1.0f, true);


  SheathWeapons(true);

}

void AMMOCharacterAbilities::OnTickAttack()
{
  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: OnTickAttack called on client"));
    return;
  }

  if (AttackAbility)
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: OnTickAttack"));
    AbilitySystem->TryActivateAbilityByClass(AttackAbility);
  }
}

void AMMOCharacterAbilities::StopAttacking()
{
  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: StopAttacking called on client"));
    return;
  }

  if (AttackState == false) return;

  AttackState = false;

  // Pause Timer By Handle
  GetWorld()->GetTimerManager().PauseTimer(AttackTimerHandle);

  SheathWeapons(false);

}

void AMMOCharacterAbilities::SheathWeapons(bool Unsheath)
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: SheathWeapons"));

  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: SheathWeapons called on client "));
    return;
  }

  switch (ActiveWeaponSlot)
  {
  case EActiveWeaponSlot::Standard:
  {
    FInventoryItem RightHandItem = EquipmentComponent->GetItemInSlot(EEquipmentSlots::RightHandWeapon);
    FInventoryItem LeftHandItem  = EquipmentComponent->GetItemInSlot(EEquipmentSlots::LeftHandWeapon);

    if (Unsheath)
    {
      RightHandMesh       = RightHandItem.EquipmentMesh;
      RightHandSheathMesh = nullptr;
      LeftHandSheathMesh  = nullptr;

      if (LeftHandItem.ItemType != EObjectType::Shield)
      {
        LeftHandMesh      = LeftHandItem.EquipmentMesh;
      }

    }
    else
    {
      RightHandMesh       = nullptr;
      RightHandSheathMesh = RightHandItem.EquipmentMesh;
      LeftHandMesh        = nullptr;

      if (LeftHandItem.ItemType != EObjectType::Shield)
      {
        LeftHandSheathMesh = LeftHandItem.EquipmentMesh;
      }
    }

    break;
  }
  case EActiveWeaponSlot::TwoHanded:
  {
    FInventoryItem TwoHandItem = EquipmentComponent->GetItemInSlot(EEquipmentSlots::TwoHandWeapon);
    
    if (Unsheath)
    {
      RightHandMesh = TwoHandItem.EquipmentMesh;
      TwoHandSheathMesh = nullptr;
    }
    else
    {
      RightHandMesh = nullptr;
      TwoHandSheathMesh = TwoHandItem.EquipmentMesh;
    }
    
    break;
  }
  case EActiveWeaponSlot::Distance:
  {
    FInventoryItem DistanceItem = EquipmentComponent->GetItemInSlot(EEquipmentSlots::DistanceWeapon);

    if (Unsheath)
    {
      RightHandMesh = DistanceItem.EquipmentMesh;
      RangedSheathMesh = nullptr;
    }
    else
    {
      RightHandMesh = nullptr;
      RangedSheathMesh = DistanceItem.EquipmentMesh;
    }

    break;
  }
  default:
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: SheathWeapons Invalid Active Weapon slot"));
    break;
  }

}

void AMMOCharacterAbilities::Server_SwitchActiveWeapon_Implementation(EActiveWeaponSlot NewActiveWeapon)
{
  SwitchActiveWeapon(NewActiveWeapon);
}

bool AMMOCharacterAbilities::Server_SwitchActiveWeapon_Validate(EActiveWeaponSlot NewActiveWeapon)
{
  return true;
}

void AMMOCharacterAbilities::SwitchActiveWeapon(EActiveWeaponSlot NewActiveWeapon)
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: SwitchActiveWeapon"));

  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: SwitchActiveWeapon called on client "));
    return;
  }

  ActiveWeaponSlot = NewActiveWeapon;

  switch (ActiveWeaponSlot)
  {
  case EActiveWeaponSlot::Standard:
  {
    Unequip(UMMOGlobalConstants::TagEquipmentSlotTwoHandWeapon,   false);
    Unequip(UMMOGlobalConstants::TagEquipmentSlotDistanceWeapon,  false);

    FInventoryItem RightHandItem = EquipmentComponent->GetItemInSlot(EEquipmentSlots::RightHandWeapon);
    FInventoryItem LeftHandItem = EquipmentComponent->GetItemInSlot(EEquipmentSlots::LeftHandWeapon);

    Equip(RightHandItem);
    Equip(LeftHandItem);

    break;
  }

  case EActiveWeaponSlot::TwoHanded:
  {
    Unequip(UMMOGlobalConstants::TagEquipmentSlotRightHandWeapon, false);
    Unequip(UMMOGlobalConstants::TagEquipmentSlotLeftHandWeapon,  false);
    Unequip(UMMOGlobalConstants::TagEquipmentSlotDistanceWeapon,  false);

    FInventoryItem TwoHandItem = EquipmentComponent->GetItemInSlot(EEquipmentSlots::TwoHandWeapon);

    Equip(TwoHandItem);

    break;
  }

  case EActiveWeaponSlot::Distance:
  {
    Unequip(UMMOGlobalConstants::TagEquipmentSlotRightHandWeapon, false);
    Unequip(UMMOGlobalConstants::TagEquipmentSlotLeftHandWeapon,  false);
    Unequip(UMMOGlobalConstants::TagEquipmentSlotTwoHandWeapon,   false);

    FInventoryItem DistanceItem = EquipmentComponent->GetItemInSlot(EEquipmentSlots::DistanceWeapon);

    Equip(DistanceItem);

    break;
  }
  default:
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: SwitchActiveWeapon Invalid Active Weapon slot"));
    break;

  }


}

void AMMOCharacterAbilities::OnGameplayEffectTagCountChanged(const FGameplayTag GameplayTag, int32 TagCount)
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: OnGameplayEffectTagCountChanged - %s - %d"), *GameplayTag.GetTagName().ToString(), TagCount);
}

void AMMOCharacterAbilities::OnAttacked(AMMOCharacterAbilities* Attacker)
{
  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: OnAttacked Character was attacked by : %s"), *Attacker->GetName());

  if (CastInterruptAbility)
  {
    AbilitySystem->TryActivateAbilityByClass(CastInterruptAbility);
  }

  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: OnAttacked TODO: StartInterruptTimer"));
}

void AMMOCharacterAbilities::Die(AMMOCharacterAbilities* Killer)
{
  if (!HasAuthority())
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: Die called on client "));
    return;
  }

  UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: Player %s was killed by: %s "), *GetName(), *Killer->GetName());

  StopAttacking();

  // TODO: list of npc and player attackers, 

  // Clear all targets
  TargetObject = nullptr;

  if (DeathAbility)
  {
    AbilitySystem->TryActivateAbilityByClass(DeathAbility);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("AMMOCharacterAbilities: Die - No Death Ability set for Object %s "), *GetName());
  }

  GetCharacterMovement()->DisableMovement();


  Multicast_Die();

}

void AMMOCharacterAbilities::Multicast_Die_Implementation()
{
  GetMesh()->SetPhysicsBlendWeight(1.0F);
}

bool AMMOCharacterAbilities::Multicast_Die_Validate()
{
  return true;
}

void AMMOCharacterAbilities::Multicast_Respawn_Implementation()
{

  GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

  GetMesh()->SetPhysicsBlendWeight(0.0F);


  FAttachmentTransformRules AttachementRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

  GetMesh()->AttachToComponent((USceneComponent*)(GetCapsuleComponent()), AttachementRules);
  
  FTransform RelativeTransform = GetMesh()->GetRelativeTransform();

  FTransform NewTransform;
  NewTransform.SetIdentity();
  NewTransform.SetLocation(FVector(0.0F, 0.0F, -97.0F));
  NewTransform.SetScale3D(RelativeTransform.GetScale3D());
  //NewTransform.SetRotation(RelativeTransform.GetRotation());

  GetMesh()->SetRelativeTransform(NewTransform, false, nullptr, ETeleportType::TeleportPhysics);


  TeleportTo(FVector(BindPosX, BindPosY, BindPosZ), FRotator(0, 0, 0));
}

bool AMMOCharacterAbilities::Multicast_Respawn_Validate()
{
  return true;
}

void AMMOCharacterAbilities::Multicast_SpawnEmitterAttached_Implementation(class UParticleSystem* EmitterTemplate, FName AttachPointName /*= NAME_None*/, FVector Location /*= FVector(ForceInit)*/, FRotator Rotation /*= FRotator::ZeroRotator*/, FVector Scale /*= FVector(1.f)*/, EAttachLocation::Type LocationType /*= EAttachLocation::KeepRelativeOffset*/, bool bAutoDestroy /*= true*/, EPSCPoolMethod PoolingMethod /*= EPSCPoolMethod::None*/, bool bAutoActivate /*= true*/)
{
  UGameplayStatics::SpawnEmitterAttached(EmitterTemplate, (USceneComponent*)GetMesh(), AttachPointName, Location, Rotation, Scale, LocationType, bAutoDestroy, PoolingMethod, bAutoActivate);
}

bool AMMOCharacterAbilities::Multicast_SpawnEmitterAttached_Validate(class UParticleSystem* EmitterTemplate, FName AttachPointName /*= NAME_None*/, FVector Location /*= FVector(ForceInit)*/, FRotator Rotation /*= FRotator::ZeroRotator*/, FVector Scale /*= FVector(1.f)*/, EAttachLocation::Type LocationType /*= EAttachLocation::KeepRelativeOffset*/, bool bAutoDestroy /*= true*/, EPSCPoolMethod PoolingMethod /*= EPSCPoolMethod::None*/, bool bAutoActivate /*= true*/)
{
  return true;
}

void AMMOCharacterAbilities::GainExperience(int32 XPAmount)
{
  Experience += XPAmount;
}

void AMMOCharacterAbilities::OnHealthChange(const FOnAttributeChangeData& Data)
{
  HealthChanged(Data.OldValue, Data.NewValue);
}

void AMMOCharacterAbilities::OnEnduranceChange(const FOnAttributeChangeData& Data)
{
  EnduranceChanged(Data.OldValue, Data.NewValue);
}

void AMMOCharacterAbilities::OnManaChange(const FOnAttributeChangeData& Data)
{
  ManaChanged(Data.OldValue, Data.NewValue);
}

void AMMOCharacterAbilities::GrantAbility(TSubclassOf<class UGameplayAbility> NewAbility, int32 AbilityLevel, AbilityInput InputID)
{
  if (AbilitySystem)
  {
    if (HasAuthority())
    {
      if (NewAbility)
      {
        if (InputID == AbilityInput::UseInputNone)
        {
          AbilitySystem->GiveAbility(FGameplayAbilitySpec(NewAbility.GetDefaultObject(), AbilityLevel, INDEX_NONE));
        }
        else
        {
          AbilitySystem->GiveAbility(FGameplayAbilitySpec(NewAbility.GetDefaultObject(), AbilityLevel, (int32)InputID));
        }
      }
    }
  }
}

void AMMOCharacterAbilities::ActivateAbility(AbilityInput InputID)
{
  if (InputID == AbilityInput::UseInputNone) return;

  if (AbilitySystem)
  {
    AbilitySystem->AbilityLocalInputPressed((int32)InputID);
  }
}

void AMMOCharacterAbilities::DeactivateAbility(AbilityInput InputID)
{
  if (InputID == AbilityInput::UseInputNone) return;

  if (AbilitySystem)
  {
    AbilitySystem->AbilityLocalInputReleased((int32)InputID);
  }
}

bool AMMOCharacterAbilities::ActivateAbilityByClass(TSubclassOf<UGameplayAbility> InAbilityToActivate, bool bAllowRemoteActivation /* = true */)
{
  if (AbilitySystem)
  {
    return AbilitySystem->TryActivateAbilityByClass(InAbilityToActivate, bAllowRemoteActivation);
  }

  return false;
}

void AMMOCharacterAbilities::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, ChestMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, ArmsMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, HandsMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, LegsMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, FeetMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, CloakMesh, COND_None, REPNOTIFY_Always);

  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, HelmMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, RightHandMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, LeftHandMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, ShieldHandMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, RightHandSheathMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, LeftHandSheathMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, TwoHandSheathMesh, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, RangedSheathMesh, COND_None, REPNOTIFY_Always);

  DOREPLIFETIME_CONDITION_NOTIFY(AMMOCharacterAbilities, IsStealthed, COND_None, REPNOTIFY_Always);

  DOREPLIFETIME(AMMOCharacterAbilities, AttackState);
  DOREPLIFETIME(AMMOCharacterAbilities, ActiveWeaponSlot);
  DOREPLIFETIME(AMMOCharacterAbilities, TargetObject);
}
