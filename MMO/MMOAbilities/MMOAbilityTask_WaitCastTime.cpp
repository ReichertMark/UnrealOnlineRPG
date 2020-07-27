// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOAbilityTask_WaitCastTime.h"
#include "TimerManager.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"

UMMOAbilityTask_WaitCastTime::UMMOAbilityTask_WaitCastTime(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
  CastTime = 0.f;
  TimeStarted = 0.f;
  RegisteredCallbacks = false;
}

UMMOAbilityTask_WaitCastTime* UMMOAbilityTask_WaitCastTime::MMOWaitCastTime(UGameplayAbility* OwningAbility, float CastTime)
{
  UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Duration(CastTime);

  auto MyObj = NewAbilityTask<UMMOAbilityTask_WaitCastTime>(OwningAbility);
  MyObj->CastTime = CastTime;
  return MyObj;
}

void UMMOAbilityTask_WaitCastTime::OnCancelCallback()
{
  if (AbilitySystemComponent)
  {
    AbilitySystemComponent->ConsumeGenericReplicatedEvent(EAbilityGenericReplicatedEvent::GenericCancel, GetAbilitySpecHandle(), GetActivationPredictionKey());
    Cancelled.Broadcast();
    EndTask();
  }
}

void UMMOAbilityTask_WaitCastTime::OnLocalCancelCallback()
{
  FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent, IsPredictingClient());

  if (AbilitySystemComponent && IsPredictingClient())
  {
    AbilitySystemComponent->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::GenericCancel, GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
  }
  OnCancelCallback();
}

void UMMOAbilityTask_WaitCastTime::Activate()
{
  UWorld* World = GetWorld();
  TimeStarted = World->GetTimeSeconds();

  FTimerHandle TimerHandleClient;
  FTimerHandle TimerHandle;


  if (AbilitySystemComponent)
  {
    const FGameplayAbilityActorInfo* Info = Ability->GetCurrentActorInfo();

    if (IsPredictingClient())
    {
      // We have to wait for the callback from the AbilitySystemComponent.
      AbilitySystemComponent->GenericLocalCancelCallbacks.AddDynamic(this, &UMMOAbilityTask_WaitCastTime::OnLocalCancelCallback);	// Tell me if the cancel input is pressed
      World->GetTimerManager().SetTimer(TimerHandleClient, this, &UMMOAbilityTask_WaitCastTime::OnCastFinishClient, CastTime, false);
      RegisteredCallbacks = true;
    }
    else
    {
      CallOrAddReplicatedDelegate(EAbilityGenericReplicatedEvent::GenericCancel, FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &UMMOAbilityTask_WaitCastTime::OnCancelCallback));
      RegisteredCallbacks = true;
      World->GetTimerManager().SetTimer(TimerHandle, this, &UMMOAbilityTask_WaitCastTime::OnCastFinish, CastTime, false);
    }
  }
}

void UMMOAbilityTask_WaitCastTime::OnDestroy(bool AbilityEnded)
{
  if (RegisteredCallbacks && AbilitySystemComponent)
  {
    AbilitySystemComponent->GenericLocalCancelCallbacks.RemoveDynamic(this, &UMMOAbilityTask_WaitCastTime::OnLocalCancelCallback);
  }

  Super::OnDestroy(AbilityEnded);
}

void UMMOAbilityTask_WaitCastTime::OnCastFinish()
{
  UE_LOG(LogTemp, Error, TEXT("OnCastFinish"));
  OnFinish.Broadcast();
  EndTask();
}

void UMMOAbilityTask_WaitCastTime::OnCastFinishClient()
{
  UE_LOG(LogTemp, Error, TEXT("OnCastFinishClient"));
  OnClientFinish.Broadcast();
  EndTask();
}

FString UMMOAbilityTask_WaitCastTime::GetDebugString() const
{
  float TimeLeft = CastTime - GetWorld()->TimeSince(TimeStarted);
  return FString::Printf(TEXT("WaitCastTime. Time: %.2f. TimeLeft: %.2f"), CastTime, TimeLeft);
}
