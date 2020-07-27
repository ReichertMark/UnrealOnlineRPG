// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "MMOCharacter.h"
#include "MMOPlayerController.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FUserCharacter
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  FString CharacterName;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 AccountSlot;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Gender;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Race;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Class;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Realm;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  FString ZoneName;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Platin;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Gold;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Silver;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Copper;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 Level;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
  int32 XP;

};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterCreateData
{
  GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateCharacter")
  FString UserId;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateCharacter")
  FString Name;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateCharacter")
  int32 AccountSlot;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateCharacter")
  int32 Gender;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateCharacter")
  int32 Race;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateCharacter")
  int32 Class;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateCharacter")
  int32 Realm;
};

/**
 * 
 */
UCLASS()
class MMO_API AMMOPlayerController : public APlayerController
{
	GENERATED_BODY()

  FHttpModule* Http;
public:
  AMMOPlayerController();

  UPROPERTY(BlueprintReadWrite, Category = "Config")
    FString WebApiPath = "";

  UFUNCTION(BlueprintCallable, Category = "Utility")
  UTexture2D* LoadTextureReference(const FString& TexturePath);


  // Character Selection (In Game)
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
   AMMOCharacter* SelectedCharacter;

   UFUNCTION(BlueprintCallable, Category = "Selection")
   void SetSelectedCharacter(AMMOCharacter* RPGCharacter);
   UFUNCTION(BlueprintCallable, Category = "Selection")
   void ClearSelectedCharacter();
   UFUNCTION(BlueprintCallable, Category = "Selection")
   void ClearSelectionOnCharacter(AMMOCharacter* RPGCharacter);
	
   //Get All Characters for UserSessionGUID
   UFUNCTION(BlueprintCallable, Category = "Login")
   void GetAllCharacters(FString UserSessionGUID);

   void OnGetAllCharactersResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void NotifyGetAllCharacters(const TArray<FUserCharacter>& UserCharacters);

   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void ErrorGetAllCharacters(const FString& ErrorMsg);

   //Create Character
   UFUNCTION(BlueprintCallable, Category = "Login")
   void CreateCharacter(FCharacterCreateData CharacterCreateData);

   void OnCreateCharacterResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void NotifyCreateCharacter(const FString& CharacterName);

   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void ErrorCreateCharacter(const FString& ErrorMsg);

   //DeleteCharacter
   UFUNCTION(BlueprintCallable, Category = "Login")
   void DeleteCharacter(FString UserSessionGUID, FString CharacterName);

   void OnDeleteCharacterResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void NotifyDeleteCharacter();
   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void ErrorDeleteCharacter(const FString& ErrorMsg);


   //Get User Session
   UFUNCTION(BlueprintCallable, Category = "Login")
   void GetUserSession(FString UserSessionGUID);

   void OnGetUserSessionResponseReceived(/*FHttpRequestPtr Request, FHttpResponsePtr Response, */bool bWasSuccessful);

   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void NotifyGetUserSession(const FString& CharacterName, const float& X, const float& Y, const float& Z, const float& RX, const float& RY, const float& RZ);
   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void ErrorGetUserSession(const FString& ErrorMsg);

   //UserSession Set Selected Character	
   UFUNCTION(BlueprintCallable, Category = "Login")
   void UserSessionSetSelectedCharacter(FString UserSessionGUID, FString SelectedCharacterName);

   void OnUserSessionSetSelectedCharacterResponseReceived(/*FHttpRequestPtr Request, FHttpResponsePtr Response, */bool bWasSuccessful);

   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void NotifyUserSessionSetSelectedCharacter();
   UFUNCTION(BlueprintImplementableEvent, Category = "Login")
   void ErrorUserSessionSetSelectedCharacter(const FString& ErrorMsg);


   //Get Last Zone Server
   UFUNCTION(BlueprintCallable, Category = "Travel")
     void GetLastZoneServerToTravelTo(FString CharacterName);

   void OnGetLastZoneServerToTravelToResponseReceived(/*FHttpRequestPtr Request, FHttpResponsePtr Response, */bool bWasSuccessful);

   UFUNCTION(BlueprintImplementableEvent, Category = "Travel")
     void NotifyLastZoneServerToTravelTo(const FString& ServerAndPort);
   UFUNCTION(BlueprintImplementableEvent, Category = "Travel")
     void ErrorLastZoneServerToTravelTo(const FString& ErrorMsg);


   UFUNCTION(BlueprintCallable, Category = "Travel")
     void TravelToMap(const FString& URL, const bool SeamlessTravel);

   UFUNCTION(BlueprintCallable, Category = "Travel")
     void TravelToMap2(const FString& ServerAndPort, const float X, const float Y, const float Z, const float RX, const float RY,
       const float RZ, const FString& PlayerName, const bool SeamlessTravel);

};
