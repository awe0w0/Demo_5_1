// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UserWidget3D.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_5_1_API UUserWidget3D : public UUserWidget
{
	
	GENERATED_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DistanceToPawn;
};
