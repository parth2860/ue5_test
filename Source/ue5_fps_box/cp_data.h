// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Http.h"
#include "JsonUtilities.h"
#include "cp_data.generated.h"

UCLASS()
class UE5_FPS_BOX_API Acp_data : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    Acp_data();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    
    //----------------------------------------------------------------------------------------------------------

    // HTTP Request Handler
    void SendHttpRequest();

    // Response Handlers
    void OnHttpResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    // Error Logger
    void LogError(const FString& ErrorMessage);

    // Print JSON raw response
    void PrintJsonResponse(const FString& JsonResponse);

    // Process JSON dynamically
    void ProcessJson(const TSharedPtr<FJsonObject>& JsonObject);

    // Helper function to process nested JSON objects and arrays dynamically
    void ProcessJsonValue(const TSharedPtr<FJsonValue>& JsonValue);

    //----------------------------------------------------------------------------------------------------------
    // Function to retrieve the parsed JSON objects
    TArray<TSharedPtr<FJsonObject>> GetParsedJsonData() const;


    // Array to hold the parsed JSON data
    TArray<TSharedPtr<FJsonObject>> ParsedJsonData;
};
