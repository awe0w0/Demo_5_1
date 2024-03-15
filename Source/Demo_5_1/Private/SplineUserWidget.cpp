// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineUserWidget.h"

#include "Kismet/GameplayStatics.h"


void USplineUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PawnMove->OnClicked.AddDynamic(this, &::USplineUserWidget::MovePawn);

	EditSpeed->OnClicked.AddDynamic(this, &::USplineUserWidget::EditSpeedOnText);

	ShowCheckBoxPanel->OnClicked.AddDynamic(this, &::USplineUserWidget::ToShowCheckBoxPanel);
	
	int ChildNum = CheckBoxPanel->GetChildrenCount();
	
	for (int i = 0; i < ChildNum; i++)
	{
		UCheckBox* Child = Cast<UCheckBox>(CheckBoxPanel->GetChildAt(i));
		Child->OnCheckStateChanged.AddDynamic(this, &::USplineUserWidget::ClickCheckBox);
	}

	UCheckBox* Child = Cast<UCheckBox>(CheckBoxPanel->GetChildAt(0));
	Child->SetCheckedState(ECheckBoxState::Checked);

	IsShowCheckBoxPanel = true;
	CheckBoxPanel->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 0; i < ChildNum; i++)
	{
		Child = Cast<UCheckBox>(CheckBoxPanel->GetChildAt(i));
		if (Child) StateArray.Push(Child->GetCheckedState() == ECheckBoxState::Checked ? 1 : 0);
	}

	float Speed = 500.f;

	Current = 0.f;

	PIsPawnMoving = false;

	Goback = false;
}

void USplineUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void USplineUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

inline void USplineUserWidget::SetLocationText(FText text)
{
	Location->SetText(text);
}

inline void USplineUserWidget::SetRotationText(FText text)
{
	Rotation->SetText(text);
}

// void USplineUserWidget::SetSplineActor(AMySpline* SplineActor)
// {
// 	this->SplineActor = SplineActor;
// }

// void USplineUserWidget::SetDefaultPawn(AMyDefaultPawn* DefaultPawn)
// {
// 	this->DefaultPawn = DefaultPawn;
// }


void USplineUserWidget::MovePawn()
{
	UE_LOG(LogTemp, Log, TEXT("Onclick"));

	DefaultPawn = Cast<AMyDefaultPawn>(GetOwningPlayerPawn());

	SplineActor = Cast<AMySpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMySpline::StaticClass()));
	
	if (!DefaultPawn->SplineDestroyed) {
		SplineActor->PIsPawnMoving = !(SplineActor->PIsPawnMoving);
	} else UE_LOG(LogTemp, Log, TEXT("SplineDestroyed"));
	// if (MPawn->SplineDestroying) UE_LOG(LogTemp, Log, TEXT("Spline Destorying"));
	// if (!MPawn->Spline) UE_LOG(LogTemp, Log, TEXT("Spline Destoryed"));
	
}

void USplineUserWidget::EditSpeedOnText()
{
	SplineActor = Cast<AMySpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMySpline::StaticClass()));
	if (SplineActor)
	{
		FString SSpeed = SpeedText->GetText().ToString();

		if (float Speed = FCString::Atof(*SSpeed))
		{
			SplineActor->Speed = Speed;
			UE_LOG(LogTemp, Log, TEXT("Speed: %.2f"), Speed);
		}else UE_LOG(LogTemp, Log, TEXT("Not A Number"));
	} else UE_LOG(LogTemp, Log, TEXT("SplineDestroyed"));
}

void USplineUserWidget::ToShowCheckBoxPanel()
{
	CheckBoxPanel->SetVisibility(IsShowCheckBoxPanel ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	IsShowCheckBoxPanel = !IsShowCheckBoxPanel;
}

void USplineUserWidget::ClickCheckBox(bool bIsChecked)
{
	
	if (CheckBoxPanel)
	{
		int Changed = 0;
		for (int i = 0; i < CheckBoxPanel->GetChildrenCount(); i++)
		{
			if (UCheckBox* Child = Cast<UCheckBox>(CheckBoxPanel->GetChildAt(i)))
			{
				if (StateArray[i] != (Child->GetCheckedState() == ECheckBoxState::Checked ? 1 : 0)) Changed = i;
				Child->SetCheckedState(ECheckBoxState::Unchecked);
			}
		}
		
		Cast<UCheckBox>(CheckBoxPanel->GetChildAt(Changed))->SetCheckedState(ECheckBoxState::Checked);
		
		for (int i = 0; i < CheckBoxPanel->GetChildrenCount(); i++)
        {
            if (UCheckBox* Child = Cast<UCheckBox>(CheckBoxPanel->GetChildAt(i)))
				StateArray[i] = Child->GetCheckedState() == ECheckBoxState::Checked ? 1 : 0;
        }
		UE_LOG(LogTemp, Log, TEXT("Number:%d Changed"), Changed);
	}
}
