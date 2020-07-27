// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOCharacterMovementComponent.h"
#include <GameFramework/Character.h>


UMMOCharacterMovementComponent::UMMOCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  IsSprinting = false;
  MaxMaxWalkSpeed = 2000.f;
}


void UMMOCharacterMovementComponent::StartSprinting()
{
  bRequestToStartSprinting = true;
}

void UMMOCharacterMovementComponent::StopSprinting()
{
  bRequestToStartSprinting = false;
}

float UMMOCharacterMovementComponent::GetMaxSpeed() const
{
  float MaxSpeed = Super::GetMaxSpeed();

  if (IsMovingForward() && bRequestToStartSprinting)
  {
    MaxSpeed *= SprintSpeedMultiplier;
  }

  return MaxSpeed;
}

float UMMOCharacterMovementComponent::GetMaxAcceleration() const
{
  float MaxAccel = Super::GetMaxAcceleration();

  if (IsMovingForward() && bRequestToStartSprinting)
  {
    MaxAccel *= SprintAccelerationMultiplier;
  }

  return MaxAccel;
}

bool UMMOCharacterMovementComponent::IsMovingForward() const
{
  if (!PawnOwner)
  {
    return false;
  }

  FVector Forward = PawnOwner->GetActorForwardVector();
  FVector TempMoveDirection = Velocity.GetSafeNormal();

  //Ignore vertical movement
  Forward.Z = 0.0f;
  TempMoveDirection.Z = 0.0f;

  float VelocityDot = FVector::DotProduct(Forward, TempMoveDirection);
  return VelocityDot > 0.7f; //Check to make sure difference between headings is not too great.
}

void UMMOCharacterMovementComponent::OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity)
{
  Super::OnMovementUpdated(DeltaTime, OldLocation, OldVelocity);

  if (!CharacterOwner)
  {
    return;
  }

  //Set Max Walk Speed
  if (bRequestMaxWalkSpeedChange)
  {
    bRequestMaxWalkSpeedChange = false;
    MaxWalkSpeed = MyNewMaxWalkSpeed;
  }

  //Dodge
  if (bWantsToDodge)
  {
    bWantsToDodge = false;

    //Only dodge if on the ground (in the air causes problems trying to get the two modes to line up due to friction)
    if (IsMovingOnGround())
    {
      MoveDirection.Normalize();
      FVector DodgeVelocity = MoveDirection * DodgeStrength;
      //Set Z component to zero so we don't go up
      DodgeVelocity.Z = 0.0f;

      Launch(DodgeVelocity);
    }
  }
}


bool UMMOCharacterMovementComponent::HandlePendingLaunch()
{
  if (!PendingLaunchVelocity.IsZero() && HasValidData())
  {
    Velocity = PendingLaunchVelocity;
    //Remmed out so our dodge move won't play the falling animation.
    //SetMovementMode(MOVE_Falling);
    PendingLaunchVelocity = FVector::ZeroVector;
    bForceNextFloorCheck = true;
    return true;
  }

  return false;
}

//============================================================================================
//Replication
//============================================================================================

//Set input flags on character from saved inputs
void UMMOCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)//Client only
{
  Super::UpdateFromCompressedFlags(Flags);

  //The Flags parameter contains the compressed input flags that are stored in the saved move.
  //UpdateFromCompressed flags simply copies the flags from the saved move into the movement component.
  //It basically just resets the movement component to the state when the move was made so it can simulate from there.
  bRequestToStartSprinting = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
  bWantsToDodge = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
  bRequestMaxWalkSpeedChange = (Flags & FSavedMove_Character::FLAG_Custom_2) != 0;
}

class FNetworkPredictionData_Client* UMMOCharacterMovementComponent::GetPredictionData_Client() const
{
  check(PawnOwner != NULL);
  check(PawnOwner->GetLocalRole() < ROLE_Authority);

  if (!ClientPredictionData)
  {
    UMMOCharacterMovementComponent* MutableThis = const_cast<UMMOCharacterMovementComponent*>(this);

    MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_MMO(*this);
    MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
    MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
  }

  return ClientPredictionData;
}

void UMMOCharacterMovementComponent::FSavedMove_MMO::Clear()
{
  Super::Clear();

  bSavedRequestToStartSprinting = false;
  bSavedRequestMaxWalkSpeedChange = false;
  SavedWalkSpeed = 0.f;
  bSavedWantsToDodge = false;
  SavedMoveDirection = FVector::ZeroVector;
}

uint8 UMMOCharacterMovementComponent::FSavedMove_MMO::GetCompressedFlags() const
{
  uint8 Result = Super::GetCompressedFlags();

  if (bSavedRequestToStartSprinting)
  {
    Result |= FLAG_Custom_0;
  }

  if (bSavedWantsToDodge)
  {
    Result |= FLAG_Custom_1;
  }

  if (bSavedRequestMaxWalkSpeedChange)
  {
    Result |= FLAG_Custom_2;
  }

  return Result;
}

bool UMMOCharacterMovementComponent::FSavedMove_MMO::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
  //Set which moves can be combined together. This will depend on the bit flags that are used.
  if (bSavedRequestToStartSprinting != ((FSavedMove_MMO*)&NewMove)->bSavedRequestToStartSprinting)
  {
    return false;
  }
  if (bSavedRequestMaxWalkSpeedChange != ((FSavedMove_MMO*)&NewMove)->bSavedRequestMaxWalkSpeedChange)
  {
    return false;
  }
  if (SavedWalkSpeed != ((FSavedMove_MMO*)&NewMove)->SavedWalkSpeed)
  {
    return false;
  }
  if (bSavedWantsToDodge != ((FSavedMove_MMO*)&NewMove)->bSavedWantsToDodge)
  {
    return false;
  }
  if (SavedMoveDirection != ((FSavedMove_MMO*)&NewMove)->SavedMoveDirection)
  {
    return false;
  }

  return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void UMMOCharacterMovementComponent::FSavedMove_MMO::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
  Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

  UMMOCharacterMovementComponent* CharacterMovement = Cast<UMMOCharacterMovementComponent>(Character->GetCharacterMovement());
  if (CharacterMovement)
  {
    bSavedRequestToStartSprinting = CharacterMovement->bRequestToStartSprinting;
    bSavedRequestMaxWalkSpeedChange = CharacterMovement->bRequestMaxWalkSpeedChange;
    SavedWalkSpeed = CharacterMovement->MyNewMaxWalkSpeed;
    bSavedWantsToDodge = CharacterMovement->bWantsToDodge;
    SavedMoveDirection = CharacterMovement->MoveDirection;
  }
}

void UMMOCharacterMovementComponent::FSavedMove_MMO::PrepMoveFor(class ACharacter* Character)
{
  Super::PrepMoveFor(Character);

  UMMOCharacterMovementComponent* CharacterMovement = Cast<UMMOCharacterMovementComponent>(Character->GetCharacterMovement());
  if (CharacterMovement)
  {
    CharacterMovement->MoveDirection = SavedMoveDirection;
    CharacterMovement->MyNewMaxWalkSpeed = SavedWalkSpeed;
  }
}

UMMOCharacterMovementComponent::FNetworkPredictionData_Client_MMO::FNetworkPredictionData_Client_MMO(const UCharacterMovementComponent& ClientMovement)
  : Super(ClientMovement)
{

}

FSavedMovePtr UMMOCharacterMovementComponent::FNetworkPredictionData_Client_MMO::AllocateNewMove()
{
  return FSavedMovePtr(new FSavedMove_MMO());
}


//Set Max Walk Speed RPC to transfer the current Max Walk Speed from the Owning Client to the Server
bool UMMOCharacterMovementComponent::Server_SetMaxWalkSpeed_Validate(const float NewMaxWalkSpeed)
{
  if (NewMaxWalkSpeed < 0.f || NewMaxWalkSpeed > MaxMaxWalkSpeed)
    return false;
  else
    return true;
}

void UMMOCharacterMovementComponent::Server_SetMaxWalkSpeed_Implementation(const float NewMaxWalkSpeed)
{
  MyNewMaxWalkSpeed = NewMaxWalkSpeed;
}

void UMMOCharacterMovementComponent::SetMaxWalkSpeed(float NewMaxWalkSpeed)
{
  if (PawnOwner->IsLocallyControlled())
  {
    MyNewMaxWalkSpeed = NewMaxWalkSpeed;
    Server_SetMaxWalkSpeed(NewMaxWalkSpeed);
  }

  bRequestMaxWalkSpeedChange = true;
}

//Dodge RPC to transfer the current Move Direction from the Owning Client to the Server
bool UMMOCharacterMovementComponent::Server_MoveDirection_Validate(const FVector& MoveDir)
{
  return true;
}

void UMMOCharacterMovementComponent::Server_MoveDirection_Implementation(const FVector& MoveDir)
{
  MoveDirection = MoveDir;
}

//Trigger the Dodge ability on the Owning Client
void UMMOCharacterMovementComponent::DoDodge()
{
  if (PawnOwner->IsLocallyControlled())
  {
    MoveDirection = PawnOwner->GetLastMovementInputVector();
    Server_MoveDirection(MoveDirection);
  }

  bWantsToDodge = true;
}