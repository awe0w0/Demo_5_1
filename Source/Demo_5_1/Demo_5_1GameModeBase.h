// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SplineUserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Demo_5_1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_5_1_API ADemo_5_1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADemo_5_1GameModeBase();

	virtual void BeginPlay() override;

private:
};
