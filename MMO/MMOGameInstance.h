// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Abilities/GameplayAbility.h"
#include "MMOGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API UMMOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
  FHttpModule* Http;

  virtual void Init() override;

  UFUNCTION()
    virtual void BeginLoadingScreen(const FString& MapName);
  UFUNCTION()
    virtual void EndLoadingScreen(UWorld* world);
  UFUNCTION(BlueprintCallable, Category = "Init")
    virtual void HideLoadingScreen();

  UFUNCTION(BlueprintImplementableEvent, Category = "Init")
    void MMOBeginLoadingScreen();
  UFUNCTION(BlueprintImplementableEvent, Category = "Init")
    void MMOEndLoadingScreen();
  UFUNCTION(BlueprintImplementableEvent, Category = "Init")
    void HideLoadingDialog();

    UFUNCTION(BlueprintCallable, Category = "Gameplay Abilities")
    TSubclassOf<UGameplayAbility> FindGameplayAbilityClass(FString ClassName) const;
  UFUNCTION(BlueprintCallable, Category = "Gameplay Abilities")
    TSubclassOf<UGameplayAbility> LoadGameplayAbilityClass(FString PathToGameplayAbilityClass) const;

};
