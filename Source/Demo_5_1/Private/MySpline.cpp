// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpline.h"

#include "CollisionActor.h"
#include "CubeWithCamera.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "WorldPartition/ContentBundle/ContentBundlePaths.h"

// Sets default values
AMySpline::AMySpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	RootComponent = Spline;

	Speed = 500.f;

	Current = 0.f;

	PIsPawnMoving = false;

	Goback = false;

	ViewBlandStart = false;
}

// Called when the game starts or when spawned
void AMySpline::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMySpline::SplineDone()
{
	UE_LOG(LogTemp, Log, TEXT("Spline Done"));
	APawn* MyPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	Goback = false;
	Current = 0.f;
	GetWorld()->GetFirstPlayerController()->SetViewTarget(MyPawn);
	Cast<ACollisionActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACollisionActor::StaticClass()))->DestroyeSpawnedActor();

	ViewBlandStart = false;

	DefaultPawn = Cast<AMyDefaultPawn>(MyPawn);
	DefaultPawn->SetFOV(90);
				
	DefaultPawn->CreateCube1();

	ACamera->Destroy();
}

// Called every frame
void AMySpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DefaultPawn = Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (Spline && UGameplayStatics::GetActorOfClass(GetWorld(), AMySpline::StaticClass())) {
		if(PIsPawnMoving) {
			if (!Goback)
			{
				SLength = Spline->GetSplineLength();

				FVector NewLoc = Spline->GetLocationAtDistanceAlongSpline(Current, ESplineCoordinateSpace::Type::World);
				FRotator NewRot = Spline->GetRotationAtDistanceAlongSpline(Current, ESplineCoordinateSpace::Type::World); 
	
				DefaultPawn->SetActorLocation(NewLoc);
				DefaultPawn->Controller->SetControlRotation(NewRot);
			
				Current += Speed / (1 / DeltaTime);

				if (Current >= SLength)
				{
					bSplineDone = true;
					Goback = true;
					ViewBlandStart = true;
				}
			}
			else 
			{ 
				if (ViewBlandStart) {
					APawn* MyPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
					FRotator Rot = FRotator(0,0,0);
					ACamera = GetWorld()->SpawnActor<AActor>(CameraActor, FTransform(Rot ,Spline->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::World)));
					GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(ACamera, 1.f);
					if (bSplineDone)
					{
						GetWorld()->GetTimerManager().SetTimer(TH, this, &AMySpline::SplineDone ,1.f);
						bSplineDone = false;
					}
					
					ViewBlandStart = false;
				}

			}
		}
	}
	
}


// TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject);
//
//
// USTRUCT()
// struct FPawnData
// {
// 	GENERATED_USTRUCT_BODY()
//
// 	UPROPERTY()
// 	int64 id;
//
// 	UPROPERTY()
// 	int32 type;
//
// 	UPROPERTY()
// 	FString name;
//
// 	UPROPERTY()
// 	float life;
//
// 	UPROPERTY()
// 	FVector pos;
//
// 	UPROPERTY()
// 	TArray<int32> states;
//
// 	FString ToString()
// 	{
// 		FString OutStr;
// 		FJsonObjectConverter::UStructToJsonObjectString(*this, OutStr, 0, 0);
// 		return OutStr;
// 	}
// 	
// };
//
//
// USTRUCT()
// struct FArrayPawnData
// {
// 	GENERATED_BODY()
//
// protected:
// 	TSharedPtr<TArray<FPawnData>> PawnDatas;
// 	FString ToString()
// 	{
// 		FString OutStr;
// 		FJsonObjectConverter::UStructToJsonObjectString(*this, OutStr);
// 		return OutStr;
// 		FJsonValue val;
// 		TSharedPtr<TJsonReader<>> Reader;
// 		
// 	}
//
// };
//
// 	struct Info
//      {
//      	FString name;
//      	int32 health;
//      };
//      
//      FString InfoCategory = "Player State";
//      TArray<Info> Players;
//      
//      struct Info info;
//      
//      info.name = TEXT("Name"); info.health = 100;
//
// 				FString OutJsonData;
// 				TSharedRef<TJsonWriter<>> Writer = TJsonReaderFactory<>::Create(&OutJsonData);
//
// 				Writer->WriteObjectStart();
// 				Writer->WriteValue(L"category", InfoCategory);
//
// 				Writer->WriteArrayStart(L"players");
// 				for (Info Player : Players)
// 				{
// 					Writer->WriteObjectStart();
// 					Writer->WriteValue(L"name", Player.name);
// 					Writer->WriteValue((L"health", Player.health));
// 					Writer->WriteObjectEnd();
// 				}
// 				Writer->WriteArrayEnd();
// 				Writer->WriteObjectEnd();
// 				Writer->Close();
//
// 				TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
//
// 				FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

