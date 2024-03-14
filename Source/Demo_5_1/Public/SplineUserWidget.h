// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySpline.h"
#include "../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/EditableText.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SplineUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_5_1_API USplineUserWidget : public UUserWidget
{
	friend class AMyPawn;
	friend class AMyDefaultPawn;
	GENERATED_BODY()

protected:


	UPROPERTY(meta = (BindWidget))
	UEditableText* SpeedText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Location;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Rotation;

	UPROPERTY(meta = (BindWidget)) 
	UButton* ShowCheckBoxPanel;
	
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* CheckBoxPanel;

	AMySpline* SplineActor;

	AMyDefaultPawn* DefaultPawn;
	
	TArray<bool> StateArray;

	float Speed;
	
	float Current;

	float SLength;
	
	bool IsShowCheckBoxPanel;

	bool PIsPawnMoving;

	bool Goback;
	
	UFUNCTION()
	void MovePawn();

	UFUNCTION()
	void EditSpeedOnText();

	UFUNCTION()
	void ToShowCheckBoxPanel();

	UFUNCTION()
	void ClickCheckBox(bool bIsChecked);
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(meta = (BindWidget))
    UButton* PawnMove;

    UPROPERTY(meta = (BindWidget))
    UButton* EditSpeed;

	void SetLocationText(FText text);

	void SetRotationText(FText text);
	
	//void SetSplineActor(AMySpline* SplineActor);

	//void SetDefaultPawn(AMyDefaultPawn* DefaultPawn);
};
