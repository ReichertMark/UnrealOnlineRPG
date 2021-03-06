// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MMOCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MMO_API UMMOCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

  class FSavedMove_MMO : public FSavedMove_Character
  {
  public:

    typedef FSavedMove_Character Super;

    ///@brief Resets all saved variables.
    virtual void Clear() override;

    ///@brief Store input commands in the compressed flags.
    virtual uint8 GetCompressedFlags() const override;

    ///@brief This is used to check whether or not two moves can be combined into one.
    ///Basically you just check to make sure that the saved variables are the same.
    virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;

    ///@brief Sets up the move before sending it to the server. 
    virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
    ///@brief Sets variables on character movement component before making a predictive correction.
    virtual void PrepMoveFor(class ACharacter* Character) override;

    //Sprint
    uint8 bSavedRequestToStartSprinting : 1;

    //Walk Speed Update
    float SavedWalkSpeed;
    uint8 bSavedRequestMaxWalkSpeedChange : 1;

    //Dodge
    FVector SavedMoveDirection;
    uint8 bSavedWantsToDodge : 1;
  };

  class FNetworkPredictionData_Client_MMO : public FNetworkPredictionData_Client_Character
  {
  public:
    FNetworkPredictionData_Client_MMO(const UCharacterMovementComponent& ClientMovement);

    typedef FNetworkPredictionData_Client_Character Super;

    ///@brief Allocates a new copy of our custom saved move
    virtual FSavedMovePtr AllocateNewMove() override;
  };

public:

  virtual bool HandlePendingLaunch() override;
  virtual void UpdateFromCompressedFlags(uint8 Flags) override;
  virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;
  void OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity);
  float GetMaxSpeed() const;
  float GetMaxAcceleration() const;

  UFUNCTION(BlueprintCallable, Category = "Movement")
  bool IsMovingForward() const;

  //Sprint
  UFUNCTION(BlueprintCallable, Category = "Sprint")
  void StartSprinting();
  UFUNCTION(BlueprintCallable, Category = "Sprint")
  void StopSprinting();

  UPROPERTY(Category = MovementMode, BlueprintReadOnly)
  bool IsSprinting;

  uint8 bRequestToStartSprinting : 1;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
  float SprintSpeedMultiplier;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
  float SprintAccelerationMultiplier;

  //Set Max Walk Speed
  UPROPERTY(EditAnywhere, Category = "Max Walk Speed")
  float MaxMaxWalkSpeed;

  uint8 bRequestMaxWalkSpeedChange : 1;

  UFUNCTION(Unreliable, Server, WithValidation)
  void Server_SetMaxWalkSpeed(const float NewMaxWalkSpeed);

  float MyNewMaxWalkSpeed;

  //Set Max Walk Speed (Called from the owning client)
  UFUNCTION(BlueprintCallable, Category = "Max Walk Speed")
  void SetMaxWalkSpeed(float NewMaxWalkSpeed);

  //Dodge
  UPROPERTY(EditAnywhere, Category = "Dodge")
  float DodgeStrength;

  UFUNCTION(Unreliable, Server, WithValidation)
  void Server_MoveDirection(const FVector& MoveDir);

  ///@brief Triggers the dodge action.
  UFUNCTION(BlueprintCallable, Category = "Dodge")
  void DoDodge();

  FVector MoveDirection;
  uint8 bWantsToDodge : 1;
	
};
