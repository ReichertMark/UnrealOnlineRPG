// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOGameInstance.h"

void UMMOGameInstance::Init()
{
  Http = &FHttpModule::Get();

  FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMMOGameInstance::BeginLoadingScreen);
  FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMMOGameInstance::EndLoadingScreen);
}

void UMMOGameInstance::BeginLoadingScreen(const FString& MapName)
{
  if (!IsRunningDedicatedServer())
  {
    MMOBeginLoadingScreen();

    /*FLoadingScreenAttributes LoadingScreen;
    LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
    LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

    GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);*/
  }
}

void UMMOGameInstance::EndLoadingScreen(UWorld* world)
{
  if (!IsRunningDedicatedServer())
  {
    MMOEndLoadingScreen();
  }
}

void UMMOGameInstance::HideLoadingScreen()
{
  if (!IsRunningDedicatedServer())
  {
    HideLoadingDialog();
  }
}

TSubclassOf<UGameplayAbility> UMMOGameInstance::FindGameplayAbilityClass(FString ClassName) const
{
  UObject* ClassPackage = ANY_PACKAGE;
  UClass* Result = FindObject<UClass>(ClassPackage, *ClassName);

  TSubclassOf<UGameplayAbility> GameplayAbilityClass = Result;

  if (GameplayAbilityClass)
    return Result;
  else
    return nullptr;
}

TSubclassOf<UGameplayAbility> UMMOGameInstance::LoadGameplayAbilityClass(FString PathToGameplayAbilityClass) const
{
  return LoadClass<UGameplayAbility>(NULL, *PathToGameplayAbilityClass, NULL, LOAD_None, NULL);
}
