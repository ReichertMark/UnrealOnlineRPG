// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "MMOGameplayEffect.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract, Blueprintable)
class MMO_API UMMOGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
  UFUNCTION(Category = MMOEffect, BlueprintPure)
  FText GetEffectName() const;

  UFUNCTION(Category = MMOEffect, BlueprintPure)
  UTexture2D* GetEffectIcon() const;

  UFUNCTION(Category = MMOEffect, BlueprintPure)
  FText GetEffectDescription() const;

protected:
  UPROPERTY(Category = "MMOEffect", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  FText EffectName;

  UPROPERTY(Category = "MMOEffect", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  UTexture2D* EffectIcon = nullptr;

  UPROPERTY(Category = "MMOEffect", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
  FText EffectDescription;


};
