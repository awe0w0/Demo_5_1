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
		StateArray.Push(Child->GetCheckedState() == ECheckBoxState::Checked ? 1 : 0);
	}

	float Speed = 500.f;

	Current = 0.f;

	PIsPawnMoving = false;

	Goback = false;
}

void USplineUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
	Super::NativeTick(MyGeometry, InDeltaTime);

	// SplineActor = Cast<AMySpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMySpline::StaticClass()));
	//
	// DefaultPawn = Cast<AMyDefaultPawn>(GetOwningPlayerPawn());
	//
	// if (SplineActor->Spline) {
	// 	if(PIsPawnMoving) {
	// 		if (!Goback)
	// 		{
	// 			FVector NewLoc = SplineActor->Spline->GetLocationAtDistanceAlongSpline(Current, ESplineCoordinateSpace::Type::Local);
	// 			FRotator NewRot = SplineActor->Spline->GetRotationAtDistanceAlongSpline(Current, ESplineCoordinateSpace::Type::Local); 
	//
	// 			DefaultPawn->Camera->SetRelativeLocation(NewLoc);
	// 			DefaultPawn->Camera->SetRelativeRotation(NewRot);
	// 		
	// 			Current += Speed / (1 / InDeltaTime);
	//
	// 			if (Current >= SLength)
	// 			{
	// 				//Current = 0.f;
	// 				//CurrentRot = Spline->GetRotationAtDistanceAlongSpline(SLength, ESplineCoordinateSpace::Type::Local);
	// 				Goback = true;
	// 			}
	// 		}
	// 		else 
	// 		{
	// 			//仿视野混合
	// 			// FVector NowLoc = Spline->GetLocationAtDistanceAlongSpline(SLength, ESplineCoordinateSpace::Type::Local);
	// 			// FVector NewLoc = Spline->GetLocationAtDistanceAlongSpline(0.f, ESplineCoordinateSpace::Type::Local);
	// 			// FRotator NowRot = Spline->GetRotationAtDistanceAlongSpline(SLength, ESplineCoordinateSpace::Type::Local);
	// 			// FRotator FirstRot = Spline->GetRotationAtDistanceAlongSpline(0.f, ESplineCoordinateSpace::Type::Local);
	// 			// FRotator NewRot = UKismetMathLibrary::Conv_VectorToRotator(NewLoc - NowLoc);
	// 			//
	// 			// float Distance = FVector::Dist(NowLoc, NewLoc);
	// 			//
	// 			// Current += Distance / (1 / InDeltaTime);
	// 			// FVector CurrentLoc = NowLoc + (NewRot.Vector() * Current);
	// 			//
	// 			// float RollDistance = FirstRot.Roll - NowRot.Roll;
	// 			// float PitchDistance = FirstRot.Pitch - NowRot.Pitch;
	// 			// float YawDistance = FirstRot.Yaw - NowRot.Yaw;
	// 			//
	// 			// if (CurrentRot.Roll != FirstRot.Roll) {
	// 			// 	CurrentRot.Roll += RollDistance  / (1 / InDeltaTime);
	// 			// 	CurrentRot.Pitch += PitchDistance  / (1 / InDeltaTime);
	// 			// 	CurrentRot.Yaw += YawDistance  / (1 / InDeltaTime);
	// 			// }
	// 			//
	// 			// Sphere->SetRelativeLocation(CurrentLoc);
	// 			// Camera->SetRelativeRotation(CurrentRot);
	//
	// 			if (Current >= 0)
	// 			{
	// 				Goback = false;
	// 				Current = 0.f;
	//
	// 				// if (UI3DIntance)
	// 				// {
	// 				// 	UI3DIntance->Destroy();
	// 				// 	UI3DIntance = nullptr;
	// 				// }
	// 				//
	// 				// if (CubeInstan)
	// 				// {
	// 				// 	CubeInstan->Destroy();
	// 				// 	CubeInstan = nullptr;
	// 				// }
	// 				
	// 				DefaultPawn->Camera->SetFieldOfView(90);
	// 			
	// 				// FVector Loc = DefaultPawn->Camera->GetComponentLocation();
	// 				// Loc.X += 500;
	// 				// Loc.Y -= 700;
	// 				// Loc.Z -= 200;
	// 			
	// 				//Cube1Instan = GetWorld()->SpawnActor<AActor>(Cube1, FTransform(Camera->GetComponentRotation(), Loc));
	//
	// 				// UMaterialInterface* MaterialB = LoadObject<UMaterialInterface>(NULL, TEXT("/Script/Engine.Material'/Game/Demo_5_1/Material/MaterialB_BP.MaterialB_BP'"));
	// 				//
	// 				// if (AMyCube1* Cube1 = Cast<AMyCube1>(Cube1Instan))
	// 				// {
	// 				// 	Cube1->SetMate(0, MaterialB);
	// 				// }
	// 				
	// 				
	// 			}
	// 		}
	// 	}
	// }
	//
	// // if (SplineDestroying)
	// // {
	// // 	if (!Spline)
	// // 	{
	// // 		UE_LOG(LogTemp, Warning, TEXT("Spline Destoryed"));
	// // 		SplineDestroying = false;
	// // 	}
	// // }
	
	// AMyDefaultPawn* MPawn = Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//
	// FVector Loc = MPawn->GetActorLocation();
	// FString StL = FString::Printf(TEXT("%f, %f, %f"), Loc.X, Loc.Y, Loc.Z);
	// Location->SetText(FText::FromString(StL));
	//
	// FRotator Rot = Cast<UCameraComponent>(MPawn->GetComponentByClass(UCameraComponent::StaticClass()))->GetComponentRotation();
	// FString StR = FString::SanitizeFloat(Rot.Roll) + ", " + FString::SanitizeFloat(Rot.Pitch) + ", " + FString::SanitizeFloat(Rot.Yaw);
	// Rotation->SetText(FText::FromString(StR));
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
			UCheckBox* Child = Cast<UCheckBox>(CheckBoxPanel->GetChildAt(i));
			if (StateArray[i] != (Child->GetCheckedState() == ECheckBoxState::Checked ? 1 : 0)) Changed = i;
			Child->SetCheckedState(ECheckBoxState::Unchecked);
		}
		
		Cast<UCheckBox>(CheckBoxPanel->GetChildAt(Changed))->SetCheckedState(ECheckBoxState::Checked);
		
		for (int i = 0; i < CheckBoxPanel->GetChildrenCount(); i++)
        {
            UCheckBox* Child = Cast<UCheckBox>(CheckBoxPanel->GetChildAt(i));
            StateArray[i] = Child->GetCheckedState() == ECheckBoxState::Checked ? 1 : 0;
        }
		UE_LOG(LogTemp, Log, TEXT("Number:%d Changed"), Changed);
	}
}
