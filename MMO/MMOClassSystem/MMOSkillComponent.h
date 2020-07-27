// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MMOAttributeSetSkills.h"
#include "MMOSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMO_API UMMOSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMMOSkillComponent();

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills, meta = (AllowPrivateAccess = "true"))
  UMMOAttributeSetSkills* AttributeSetSkills;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
