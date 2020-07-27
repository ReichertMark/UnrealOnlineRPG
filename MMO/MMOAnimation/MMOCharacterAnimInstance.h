// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MMO/MMOInterfaces/MMOCharacterAnimationInterface.h"
#include "MMOCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API UMMOCharacterAnimInstance : public UAnimInstance, public IMMOCharacterAnimationInterface
{
	GENERATED_BODY()
	
};
