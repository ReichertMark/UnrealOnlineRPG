// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOActorWidgetComponent.h"
#include "MMOActorWidget.h"

UMMOActorWidgetComponent::UMMOActorWidgetComponent()
{
  // Set common defaults when using widgets on Actors
  SetDrawAtDesiredSize(true);
  SetWidgetSpace(EWidgetSpace::Screen);
  SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UMMOActorWidgetComponent::InitWidget()
{
  // Base implementation creates the 'Widget' instance
  Super::InitWidget();

  if (Widget)
  {
#if !UE_BUILD_SHIPPING
    if (!Widget->IsA(UMMOActorWidget::StaticClass()))
    {
      // Suggest deriving from actor widget (not strictly required, but you lose the benefit of auto-assigning the Actor this way)
      UE_LOG(LogTemp, Warning, TEXT("WidgetClass for %s does not derive from UMMOCharacterWidgetComponent"), *GetNameSafe(GetOwner()));
    }
#endif
    UMMOActorWidget* WidgetInst = Cast<UMMOActorWidget>(Widget);
    if (WidgetInst)
    {
      // Assign the owner, now we have easy access in the widget itself
      WidgetInst->SetOwningActor(GetOwner());
    }
  }
}
