// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySpline.h"
#include "SpawnSplineCube.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/EditableText.h"
#include "JsonRequest.h"
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
	UButton* ShowJsonOnLog;
	
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* CheckBoxPanel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpawnSplineCube> SpawnSplineCube;

	AActor* SpawnSplineCubeInstan;

	AMySpline* SplineActor;

	AMyDefaultPawn* DefaultPawn;

	AJsonRequest* JsonRequest;
	
	TArray<bool> StateArray;
	
	bool IsShowCheckBoxPanel;
	
	UFUNCTION()
	void MovePawn();

	UFUNCTION()
	void EditSpeedOnText();

	UFUNCTION()
	void ToShowCheckBoxPanel();

	UFUNCTION()
	void ClickCheckBox(bool bIsChecked);

	UFUNCTION()
	void ShowLogAndCreateGCube();

	UFUNCTION()
	void OnRequestSucceed(TArray<FUserState> UserStates, bool smt, int8 fmt, float V);

	UFUNCTION()
	void OnRequestFailed(TArray<FUserState> UserStates, bool smt, int8 fmt, float V);
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(meta = (BindWidget))
    UButton* PawnMove;

    UPROPERTY(meta = (BindWidget))
    UButton* EditSpeed;

	void SetLocationText(FText text);

	void SetRotationText(FText text);
	
};
