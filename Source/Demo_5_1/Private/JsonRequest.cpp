// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonRequest.h"

#include <Windows.Data.Xml.Dom.h>

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

FUserState::FUserState()
{
	UUID = "";
	name = "";
	Num = 0;
	SecData = 0;
	
	P.O.X = 0;
	P.O.Y = 0;
	P.O.Z = 0;
	P.R.Pitch = 0;
	P.R.Roll = 0;
	P.R.Yaw = 0;
}

// Sets default values
AJsonRequest::AJsonRequest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJsonRequest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJsonRequest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJsonRequest::HttpRequestStart(FString URL)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb("Get");
	Request->SetURL(URL);

	Request->OnProcessRequestComplete().BindUObject(this, &AJsonRequest::HttpRequestComplete);
	Request->ProcessRequest();
}

void AJsonRequest::HttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			const TArray<TSharedPtr<FJsonValue>>* DataList;
			if (JsonObject->TryGetArrayField(TEXT("data"), DataList))
			{
				TArray<FUserState> NewList;
				for (TSharedPtr<FJsonValue> Item : *DataList)
				{
					TSharedPtr<FJsonObject> ItemObject = Item->AsObject();

					FUserState UserState;

					UserState.UUID = ItemObject->GetStringField(TEXT("UUID"));
					UserState.name = ItemObject->GetStringField(TEXT("name"));
					UserState.Num = ItemObject->GetIntegerField(TEXT("Num"));
					UserState.SecData = ItemObject->GetIntegerField(TEXT("SecData"));
					
					TSharedPtr<FJsonObject> P = ItemObject->GetObjectField(TEXT("P"));
					
					if (P->HasField(TEXT("O")))
					{
						auto OList = P->GetArrayField(TEXT("O"));
						UserState.P.O.X = OList[0]->AsNumber();
						UserState.P.O.Y = OList[1]->AsNumber();
						UserState.P.O.Z = OList[2]->AsNumber();
					}
					
					if (P->HasField(TEXT("R")))
					{
						auto RList = P->GetArrayField(TEXT("R"));
						UserState.P.R.Pitch = RList[0]->AsNumber();
						UserState.P.R.Roll = RList[1]->AsNumber();
						UserState.P.R.Yaw = RList[2]->AsNumber();
					}

					NewList.Add(UserState);
				}
				bool smt = JsonObject->GetBoolField(TEXT("smt"));
				int8 fmt = JsonObject->GetIntegerField(TEXT("fmt"));
				float V = JsonObject->GetNumberField(TEXT("V"));
				
				OnSucceed.Broadcast(NewList, smt, fmt, V);
			}
		}
	}
	else
	{
		OnFailed.Broadcast({}, 0, 0, 0);
	}
}

