// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MMOActorWidgetComponent.generated.h"

/**
 * Extension of the WidgetComponent to make it easy to have owning Actor context to the Widget. Commonly used to display health bars, names, and interaction panels above Actors.
  Automatically calls SetOwningActor on the widget if the correct type of widget is used (MMOActorWidget)
 */
UCLASS(ClassGroup = (MMO), meta = (BlueprintSpawnableComponent))
class MMO_API UMMOActorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
  UMMOActorWidgetComponent();

  virtual void InitWidget() override;
};