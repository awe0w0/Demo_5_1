// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineUserWidget.h"

#include "Http.h"
#include "JsonRequest.h"
#include "Kismet/GameplayStatics.h"


void USplineUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PawnMove->OnClicked.AddDynamic(this, &::USplineUserWidget::MovePawn);

	EditSpeed->OnClicked.AddDynamic(this, &::USplineUserWidget::EditSpeedOnText);

	ShowCheckBoxPanel->OnClicked.AddDynamic(this, &::USplineUserWidget::ToShowCheckBoxPanel);
 
	ShowJsonOnLog->OnClicked.AddDynamic(this, &::USplineUserWidget::ShowLogAndCreateGCube);

	JsonRequest = Cast<AJsonRequest>(UGameplayStatics::GetActorOfClass(GetWorld(), AJsonRequest::StaticClass()));	
	JsonRequest->OnSucceed.AddDynamic(this, &::USplineUserWidget::OnRequestSucceed);
	JsonRequest->OnFailed.AddDynamic(this, &::USplineUserWidget::OnRequestFailed);
	
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
}

void USplineUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

inline void USplineUserWidget::SetLocationText(FText text)
{
	Location->SetText(text);
}

inline void USplineUserWidget::SetRotationText(FText text)
{
	Rotation->SetText(text);
}

void USplineUserWidget::MovePawn()
{
	UE_LOG(LogTemp, Log, TEXT("Onclick"));

	DefaultPawn = Cast<AMyDefaultPawn>(GetOwningPlayerPawn());

	SplineActor = Cast<AMySpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMySpline::StaticClass()));
	
	if (SplineActor) {
		SplineActor->PIsPawnMoving = !(SplineActor->PIsPawnMoving);
	} else UE_LOG(LogTemp, Log, TEXT("SplineDestroyed"));
	
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
		}else
		{
			UE_LOG(LogTemp, Log, TEXT("Not A Number"));
		}
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

void USplineUserWidget::ShowLogAndCreateGCube()
{
	FString URL = "http://127.0.0.1:2677/Test/Test1";
	JsonRequest->HttpRequestStart(URL);
}

void USplineUserWidget::OnRequestSucceed(TArray<FUserState> UserStates, bool smt, int8 fmt, float V)
{
	UE_LOG(LogHttp, Warning, TEXT("smt: %d, fmt: %d"), smt, fmt);

	Cast<AJsonRequest>(UGameplayStatics::GetActorOfClass(GetWorld(), AJsonRequest::StaticClass()))->JsonMap.Reset();

	for(FUserState UserState : UserStates) {
		UE_LOG(LogHttp, Warning, TEXT("UUID: %s, name: %s, Num: %d, SecData: %lld, P.O.X: %f, P.O.Y: %f, P.O.Z: %f, P.R.Pitch: %f, P.R.Roll: %f, P.R.Yaw: %f"),
		   *UserState.UUID, *UserState.name, UserState.Num, UserState.SecData, UserState.P.O.X, UserState.P.O.Y, UserState.P.O.Z, UserState.P.R.Pitch, UserState.P.R.Roll, UserState.P.R.Yaw);

		FString UUIDLastTwoNumber = UserState.UUID.Right(2);
		
	 	if (FCString::Atoi64(*UUIDLastTwoNumber))
	 	{
	 		Cast<AJsonRequest>(UGameplayStatics::GetActorOfClass(GetWorld(), AJsonRequest::StaticClass()))->JsonMap.Add(FCString::Atoi64(*UUIDLastTwoNumber), UserState);
	 	}
	 	else {UE_LOG(LogTemp, Warning, TEXT("UUID Not A Number"));}
	 }
	UE_LOG(LogHttp, Warning, TEXT("V: %f"), V);

	Cast<AJsonRequest>(UGameplayStatics::GetActorOfClass(GetWorld(), AJsonRequest::StaticClass()))->
		JsonMap.KeySort([](int vala, int valb) -> bool {return vala < valb;});

	for (TPair<int, FUserState> State : Cast<AJsonRequest>(UGameplayStatics::GetActorOfClass(GetWorld(), AJsonRequest::StaticClass()))->JsonMap)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *State.Value.UUID);
	}

	 if (!UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnSplineCube::StaticClass())) {
		FVector Loc = Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetActorLocation();
		Loc.X += 700;
		Loc.Y -= 1000;
		Loc.Z -= 200;

		FRotator Rotator = FRotator(0, 0, 0);
	
		SpawnSplineCubeInstan = GetWorld()->SpawnActor<AActor>(SpawnSplineCube, FTransform(Rotator, Loc));

		UMaterialInterface* MaterialC = LoadObject<UMaterialInterface>(NULL, TEXT("/Script/Engine.Material'/Game/Demo_5_1/Material/MaterialC_BP.MaterialC_BP'"));

		if (ASpawnSplineCube* SpawnSplineCubeM = Cast<ASpawnSplineCube>(SpawnSplineCubeInstan))
		{
			SpawnSplineCubeM->SetMate(0, MaterialC);
		}
	}
	
}

void USplineUserWidget::OnRequestFailed(TArray<FUserState> UserStates, bool smt, int8 fmt, float V)
{
}
