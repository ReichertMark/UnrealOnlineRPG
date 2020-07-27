// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOLoginWidget.h"
#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"
#include <Serialization/JsonSerializer.h>



void UMMOLoginWidget::LoginAndCreateSession(FString Email, FString Password)
{
  Http = &FHttpModule::Get();
  Http->SetHttpTimeout(LoginTimeout); //Set timeout

  GConfig->GetString(
    TEXT("/Script/EngineSettings.GeneralProjectSettings"),
    TEXT("WebApiPath"),
    WebApiPath,
    GGameIni
  );

  TSharedRef<IHttpRequest> Request = Http->CreateRequest();
  Request->OnProcessRequestComplete().BindUObject(this, &UMMOLoginWidget::OnLoginAndCreateSessionResponseReceived);

  FString url = FString(TEXT("http://" + WebApiPath + "/account/LoginAndCreateSession"));

  FString PostParameters = "{\"Email\":\"" + Email + "\",\"Password\":\"" + Password + "\"}";

  if (Email.IsEmpty() && Password.IsEmpty())
  {
    PostParameters = "{\"Email\":\"SuperAdmin@mail.com\",\"Password\":\"Abc123!\"}";
  }

  Request->SetURL(url);
  Request->SetVerb("POST");
  Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
  Request->SetHeader("Content-Type", TEXT("application/json"));
  Request->SetContentAsString(PostParameters);
  Request->ProcessRequest();
}

void UMMOLoginWidget::OnLoginAndCreateSessionResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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
        ErrorLoginAndCreateSession(*ErrorMessage);
        return;
      }

      FString UserId = JsonObject->GetStringField("UserId");
      UE_LOG(LogTemp, Warning, TEXT("Login Succeeded with User ID: %s"), *UserId);

      NotifyLoginAndCreateSession(UserId);
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("OnUserLoginResponseReceived Server returned no data!"));
      ErrorLoginAndCreateSession(TEXT("Unknown login error!"));
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("OnUserLoginResponseReceived Error accessing login server!"));
    ErrorLoginAndCreateSession(TEXT("Unknown error connecting to server!"));
  }
}

void UMMOLoginWidget::OpenCreateAccountInBrowser()
{
  FString TheURL = "http://localhost:44365/home";
  FPlatformProcess::LaunchURL(*TheURL, nullptr, nullptr);
}
