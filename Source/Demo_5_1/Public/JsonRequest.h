// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "JsonRequest.generated.h"

USTRUCT()
struct FO
{
	GENERATED_BODY()
	float X;
	float Y;
	float Z;
};

USTRUCT()
struct FR
{
	GENERATED_BODY()
	float Pitch;
	float Roll;
	float Yaw;
};

USTRUCT()
struct FP
{
	GENERATED_BODY()

	FO O;
	FR R;
	
};

USTRUCT()
struct FUserState
{
	GENERATED_BODY()

	FUserState();
	
	FString UUID;
	FString name;
	int32 Num;
	int64 SecData;

	FP P;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FUserStateDataReceive, TArray<FUserState>, UserStates, bool, smt, int8, fmt, float, V);

UCLASS()
class DEMO_5_1_API AJsonRequest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJsonRequest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HttpRequestStart(FString URL);
	
	void HttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	FUserStateDataReceive OnSucceed;
	FUserStateDataReceive OnFailed;

	TMap<int64, FUserState> JsonMap;
};
