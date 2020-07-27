// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOPlayerController.h"

#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <JsonObjectConverter.h>

AMMOPlayerController::AMMOPlayerController()
{
  GConfig->GetString(
    TEXT("/Script/EngineSettings.GeneralProjectSettings"),
    TEXT("WebApiPath"),
    WebApiPath,
    GGameIni
  );

  bEnableClickEvents = true;
}


UTexture2D* AMMOPlayerController::LoadTextureReference(const FString& TexturePath)
{
  FStringAssetReference TextureReference(TexturePath);
  return Cast<UTexture2D>(TextureReference.TryLoad());
}

void AMMOPlayerController::SetSelectedCharacter(AMMOCharacter* RPGCharacter)
{
  if (SelectedCharacter)
  {
    ClearSelectionOnCharacter(SelectedCharacter);
  }

  if (RPGCharacter)
  {
    TArray<UActorComponent*> SMcomps;

    RPGCharacter->GetComponents(SMcomps);
    for (int i = 0; i < SMcomps.Num(); ++i) //Because there may be more components
    {
      UStaticMeshComponent* thisSMComp = Cast<UStaticMeshComponent>(SMcomps[i]); //try to cast to static mesh component
      if (thisSMComp)
      {
        thisSMComp->SetRenderCustomDepth(true);
        thisSMComp->SetCustomDepthStencilValue(252);
      }

      USkeletalMeshComponent* thisSKMComp = Cast<USkeletalMeshComponent>(SMcomps[i]); //try to cast to static mesh component
      if (thisSKMComp)
      {
        thisSKMComp->SetRenderCustomDepth(true);
        thisSKMComp->SetCustomDepthStencilValue(252);
      }
    }

    SelectedCharacter = RPGCharacter;
  }
}

void AMMOPlayerController::ClearSelectedCharacter()
{
  if (SelectedCharacter)
  {
    AMMOCharacter* RPGCharacter = SelectedCharacter;
    TArray<UActorComponent*> SMcomps;

    RPGCharacter->GetComponents(SMcomps);
    for (int i = 0; i < SMcomps.Num(); ++i) //Because there may be more components
    {
      UStaticMeshComponent* thisSMComp = Cast<UStaticMeshComponent>(SMcomps[i]); //try to cast to static mesh component
      if (thisSMComp)
      {
        //if (thisSMComp->CustomDepthStencilValue != 254)
        //{
        thisSMComp->SetRenderCustomDepth(false);
        thisSMComp->SetCustomDepthStencilValue(0);
        //}
      }

      USkeletalMeshComponent* thisSKMComp = Cast<USkeletalMeshComponent>(SMcomps[i]); //try to cast to static mesh component
      if (thisSKMComp)
      {
        //if (thisSKMComp->CustomDepthStencilValue != 254)
        //{
        thisSKMComp->SetRenderCustomDepth(false);
        thisSKMComp->SetCustomDepthStencilValue(0);
        //}
      }
    }

    SelectedCharacter = NULL;
  }
}

void AMMOPlayerController::ClearSelectionOnCharacter(AMMOCharacter* RPGCharacter)
{
  if (RPGCharacter)
  {
    TArray<UActorComponent*> SMcomps;

    RPGCharacter->GetComponents(SMcomps);
    for (int i = 0; i < SMcomps.Num(); ++i) //Because there may be more components
    {
      UStaticMeshComponent* thisSMComp = Cast<UStaticMeshComponent>(SMcomps[i]); //try to cast to static mesh component
      if (thisSMComp)
      {
        //if (thisSMComp->CustomDepthStencilValue != 254)
        //{
        thisSMComp->SetRenderCustomDepth(false);
        thisSMComp->SetCustomDepthStencilValue(0);
        //}
      }

      USkeletalMeshComponent* thisSKMComp = Cast<USkeletalMeshComponent>(SMcomps[i]); //try to cast to static mesh component
      if (thisSKMComp)
      {
        //if (thisSKMComp->CustomDepthStencilValue != 254)
        //{
        thisSKMComp->SetRenderCustomDepth(false);
        thisSKMComp->SetCustomDepthStencilValue(0);
        //}
      }
    }

    SelectedCharacter = NULL;
  }
}

void AMMOPlayerController::GetAllCharacters(FString UserSessionGUID)
{
  Http = &FHttpModule::Get();

  TSharedRef<IHttpRequest> Request = Http->CreateRequest();
  Request->OnProcessRequestComplete().BindUObject(this, &AMMOPlayerController::OnGetAllCharactersResponseReceived);
  //This is the url on which to process the request
  FString url = FString(TEXT("http://" + WebApiPath + "/character/GetAllCharacters?userId=" + UserSessionGUID));

  FString PostParameters = FString(TEXT("userId=")) + UserSessionGUID;

  Request->SetURL(url);
  Request->SetVerb("GET");
  Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
  Request->SetHeader("Content-Type", TEXT("application/json"));
  Request->SetContentAsString("");
  Request->ProcessRequest();
}

void AMMOPlayerController::OnGetAllCharactersResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
  if (bWasSuccessful)
  {
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
      FString ErrorMessage = JsonObject->GetStringField("ErrorMessage");

      if (!ErrorMessage.IsEmpty())
      {
        ErrorGetAllCharacters(*ErrorMessage);
        return;
      }

      TArray<FUserCharacter> UsersCharactersData;

      if (JsonObject->HasField("characters"))
      {
        TArray<TSharedPtr<FJsonValue>> Rows = JsonObject->GetArrayField("characters");
        UE_LOG(LogTemp, Warning, TEXT("HasField"));

        for (int RowNum = 0; RowNum != Rows.Num(); RowNum++) 
        {
          FUserCharacter tempUserCharacter;
          TSharedPtr<FJsonObject> tempRow = Rows[RowNum]->AsObject();
          tempUserCharacter.CharacterName = tempRow->GetStringField("Name");
          tempUserCharacter.AccountSlot = tempRow->GetNumberField("AccountSlot");
          tempUserCharacter.Gender = tempRow->GetNumberField("Gender");
          tempUserCharacter.Race = tempRow->GetNumberField("Race");
          tempUserCharacter.Class = tempRow->GetNumberField("Class");
          tempUserCharacter.Level = tempRow->GetNumberField("Realm");
          //tempUserCharacter.ZoneName = tempRow->GetStringField("MapName");
          //tempUserCharacter.Gold = tempRow->GetNumberField("Gold");
          //tempUserCharacter.Silver = tempRow->GetNumberField("Silver");
          //tempUserCharacter.Copper = tempRow->GetNumberField("Copper");
          //tempUserCharacter.FreeCurrency = tempRow->GetNumberField("FreeCurrency");
         // tempUserCharacter.PremiumCurrency = tempRow->GetNumberField("PremiumCurrency");
          //tempUserCharacter.Score = tempRow->GetNumberField("Score");
          //tempUserCharacter.XP = tempRow->GetNumberField("XP");

          
          UE_LOG(LogTemp, Error, TEXT("Character: Name=%s Realm=%d Race=%d AccountSlot=%d"), *tempUserCharacter.CharacterName, tempUserCharacter.Level, tempUserCharacter.Gender, tempUserCharacter.AccountSlot);

          UsersCharactersData.Add(tempUserCharacter);
        }
      }

      NotifyGetAllCharacters(UsersCharactersData);
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("OnGetAllCharactersResponseReceived Server returned no data!"));
      ErrorGetAllCharacters(TEXT("Unknown login error!"));
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("OnGetAllCharactersResponseReceived Error accessing login server!"));
    ErrorGetAllCharacters(TEXT("Unknown error connecting to server!"));
  }
}

void AMMOPlayerController::CreateCharacter(FCharacterCreateData CharacterCreateData)
{
  Http = &FHttpModule::Get();

  TSharedRef<IHttpRequest> Request = Http->CreateRequest();
  Request->OnProcessRequestComplete().BindUObject(this, &AMMOPlayerController::OnCreateCharacterResponseReceived);
  //This is the url on which to process the request
  FString url = FString(TEXT("http://" + WebApiPath + "/character/create"));


  FString PostParameters;


  if (!FJsonObjectConverter::UStructToJsonObjectString(CharacterCreateData, PostParameters, 0, 0, 0, nullptr, false))
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to Convert CharacterCreateData to JSon Struct!"));
    return;
  }
  UE_LOG(LogTemp, Error, TEXT("Json String: %s"), *PostParameters);

  Request->SetURL(url);
  Request->SetVerb("POST");
  Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
  Request->SetHeader("Content-Type", TEXT("application/json"));
  Request->SetContentAsString(PostParameters);
  Request->ProcessRequest();
}

void AMMOPlayerController::OnCreateCharacterResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
  if (bWasSuccessful)
  {
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
      FString ErrorMessage = JsonObject->GetStringField("ErrorMessage");

      if (!ErrorMessage.IsEmpty())
      {
        ErrorCreateCharacter(*ErrorMessage);
        return;
      }

      FString tempCharacterName = JsonObject->GetStringField("CharacterName");

      NotifyCreateCharacter(tempCharacterName);
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("OnCreateCharacterResponseReceived Server returned no data!"));
      ErrorCreateCharacter(TEXT("Unknown login error!"));
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("OnCreateCharacterResponseReceived Error accessing login server!"));
    ErrorCreateCharacter(TEXT("Unknown error connecting to server!"));
  }
}

void AMMOPlayerController::DeleteCharacter(FString UserSessionGUID, FString CharacterName)
{
  Http = &FHttpModule::Get();

  TSharedRef<IHttpRequest> Request = Http->CreateRequest();
  Request->OnProcessRequestComplete().BindUObject(this, &AMMOPlayerController::OnDeleteCharacterResponseReceived);
  //This is the url on which to process the request
  FString url = FString(TEXT("http://" + WebApiPath + "/character/Delete?characterName=" + CharacterName));

  Request->SetURL(url);
  Request->SetVerb("POST");
  Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
  Request->SetHeader("Content-Type", TEXT("application/json"));
  Request->SetContentAsString("");
  Request->ProcessRequest();
}

void AMMOPlayerController::OnDeleteCharacterResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
  if (bWasSuccessful)
  {
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
      FString ErrorMessage = JsonObject->GetStringField("ErrorMessage");

      if (!ErrorMessage.IsEmpty())
      {
        UE_LOG(LogTemp, Verbose, TEXT("OnRemoveCharacterResponseReceived Error: %s"), *ErrorMessage);
        ErrorDeleteCharacter(ErrorMessage);
      }
      else
      {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteCharacterResponseReceived Success!"));
        NotifyDeleteCharacter();
      }
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("OnRemoveCharacterResponseReceived Server returned no data!"));
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("OnRemoveCharacterResponseReceived Error accessing server!"));
  }
}

void AMMOPlayerController::GetUserSession(FString UserSessionGUID)
{
  OnGetUserSessionResponseReceived(true);
}

void AMMOPlayerController::OnGetUserSessionResponseReceived(/*FHttpRequestPtr Request, FHttpResponsePtr Response, */bool bWasSuccessful)
{
  float X = -12330.0f;
  float Y = -172420.0f;
  float Z = -10450.0f;
  float RX  = 0.0f;
  float RY  = 0.0f;
  float RZ  = 0.0f;

  UE_LOG(LogTemp, Log, TEXT("GetUserSession location is %f, %f, %f"), X, Y, Z);

  NotifyGetUserSession("TestCharacter", X, Y, Z, RX, RY, RZ);
}

void AMMOPlayerController::UserSessionSetSelectedCharacter(FString UserSessionGUID, FString SelectedCharacterName)
{
  OnUserSessionSetSelectedCharacterResponseReceived(true);
}

void AMMOPlayerController::OnUserSessionSetSelectedCharacterResponseReceived(/*FHttpRequestPtr Request, FHttpResponsePtr Response, */bool bWasSuccessful)
{
  NotifyUserSessionSetSelectedCharacter();
}

void AMMOPlayerController::GetLastZoneServerToTravelTo(FString CharacterName)
{
  OnGetLastZoneServerToTravelToResponseReceived(true);
}

void AMMOPlayerController::OnGetLastZoneServerToTravelToResponseReceived(/*FHttpRequestPtr Request, FHttpResponsePtr Response, */bool bWasSuccessful)
{
  FString ServerIP = "localhost";//JsonObject->GetStringField("serverip");
  FString Port = "1234";//JsonObject->GetStringField("port");

  FString ServerAndPort = "127.0.0.1:8181";//"/Game/ThirdPersonCPP/Maps/Celts/Map_Celts.Map_Celts";//ServerIP + FString(TEXT(":")) + Port.Left(4);

  NotifyLastZoneServerToTravelTo(ServerAndPort);
}

void AMMOPlayerController::TravelToMap(const FString& URL, const bool SeamlessTravel)
{
  UE_LOG(LogTemp, Warning, TEXT("TravelToMap: %s"), *URL);
  ClientTravel(URL, TRAVEL_Absolute, false, FGuid());
}

void AMMOPlayerController::TravelToMap2(const FString& ServerAndPort, const float X, const float Y, const float Z, const float RX, const float RY, const float RZ, const FString& PlayerName, const bool SeamlessTravel)
{
//   FString URL = ServerAndPort
//     + FString(TEXT("?PLX=")) + FString::SanitizeFloat(X)
//     + FString(TEXT("?PLY=")) + FString::SanitizeFloat(Y)
//     + FString(TEXT("?PLZ=")) + FString::SanitizeFloat(Z)
//     + FString(TEXT("?PRX=")) + FString::SanitizeFloat(RX)
//     + FString(TEXT("?PRY=")) + FString::SanitizeFloat(RY)
//     + FString(TEXT("?PRZ=")) + FString::SanitizeFloat(RZ)
//     + FString(TEXT("?Player=")) + FGenericPlatformHttp::UrlEncode(PlayerName);

  //FString URL = "/Game/ThirdPersonCPP/Maps/Celts/Map_Celts.Map_Celts" // "localhost:8181"
  FString URL = ServerAndPort //"localhost:8181"
    + FString(TEXT("?PLX=")) + FString::SanitizeFloat(X)
    + FString(TEXT("?PLY=")) + FString::SanitizeFloat(Y)
    + FString(TEXT("?PLZ=")) + FString::SanitizeFloat(Z)
    + FString(TEXT("?PRX=")) + FString::SanitizeFloat(RX)
    + FString(TEXT("?PRY=")) + FString::SanitizeFloat(RY)
    + FString(TEXT("?PRZ=")) + FString::SanitizeFloat(RZ)
    + FString(TEXT("?Player=")) + FGenericPlatformHttp::UrlEncode(PlayerName);

  UE_LOG(LogTemp, Warning, TEXT("TravelToMap: %s"), *URL);
  ClientTravel(URL, TRAVEL_Absolute, false, FGuid());
  
}
