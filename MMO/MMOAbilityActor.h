// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h" 
#include "MMOAttributeSetSimple.h"
#include "MMOAbilityActor.generated.h"

UCLASS()
class MMO_API AMMOAbilityActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMMOAbilityActor();

  virtual void PostInitializeComponents() override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
  class UAbilitySystemComponent* AbilitySystem;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
  UMMOAttributeSetSimple* MMOAttributesSimple;

  UAbilitySystemComponent* GetAbilitySystemComponent() const override
  {
    return AbilitySystem;
  };

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;



};
