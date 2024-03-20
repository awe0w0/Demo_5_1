// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionActor.h"

#include "MyCube.h"
#include "MyDefaultPawn.h"
#include "SplineUserWidget.h"
#include "Brushes/SlateColorBrush.h"

// Sets default values
ACollisionActor::ACollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &::ACollisionActor::BeginOverlap);


}

// Called when the game starts or when spawned
void ACollisionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollisionActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Create3DUI();
	
	CreateCube();
	
	SetButtonColor();
}

// Called every frame
void ACollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollisionActor::Create3DUI()
{
	UE_LOG(LogTemp, Log, TEXT("Componet overlap"));

	//UClass* UI = LoadClass<AUI3D>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Demo_5_1/UI3D_BP.UI3D_BP_C'"));
	AMyDefaultPawn* MyPawn = Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	FVector Loc = MyPawn->GetActorLocation();
	Loc.Y -= 500;
	Loc.Z -= 200;
	
	UI3DIntance = GetWorld()->SpawnActor<AActor>(UI3D, FTransform(GetActorRotation(), Loc));
}

void ACollisionActor::CreateCube()
{
	AMyDefaultPawn* MyPawn = Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FVector Loc = MyPawn->GetActorLocation();
	Loc.Y -= 1000;
	Loc.Z -= 200;

	CubeInstan = GetWorld()->SpawnActor<AActor>(Cube, FTransform(MyPawn->GetActorRotation(), Loc));

	UMaterialInterface* MaterialA = LoadObject<UMaterialInterface>(NULL, TEXT("/Script/Engine.Material'/Game/Demo_5_1/Material/MaterialA_BP.MaterialA_BP'"));
	

	if (AMyCube* CubeM = Cast<AMyCube>(CubeInstan))
	{
		CubeM->SetMate(0, MaterialA);
		
	}

	GetWorld()->GetTimerManager().SetTimer(TH1, this, &ACollisionActor::SetCubeMaterial, 1.f);
}

void ACollisionActor::SetButtonColor()
{
	UE_LOG(LogTemp, Log, TEXT("Button Color"));
	
	MyWidgetInstance->EditSpeed->SetStyle(FButtonStyle().SetNormal(FSlateColorBrush(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f))));
	
	GetWorld()->GetTimerManager().SetTimer(TH, this, &ACollisionActor::ButtonBImageAndCameraFOV, 3.f);
}

void ACollisionActor::ButtonBImageAndCameraFOV()
{
	const FLinearColor Color(1.0f, 1.0f, 1.0f, 1.0f);
	FSlateBrush NewBrush;
	NewBrush.TintColor = FSlateColor(Color);
	NewBrush.SetResourceObject(LoadObject<UObject>(NULL,TEXT("/Script/Engine.Texture2D'/Game/Demo_5_1/v2-8b14a2eff8c3a6e4f300f6e9445999be_720w.v2-8b14a2eff8c3a6e4f300f6e9445999be_720w'")));

	FButtonStyle BStyle = MyWidgetInstance->PawnMove->WidgetStyle;
	BStyle.SetNormal(NewBrush);
	
	MyWidgetInstance->PawnMove->SetStyle(BStyle);

	// UCameraComponent* Camera = Cast<UCameraComponent>(Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetComponentByClass(UCameraComponent::StaticClass()));
	Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->SetFOV(130);
}

void ACollisionActor::SetCubeMaterial()
{
	UE_LOG(LogTemp, Log, TEXT("Cube Set Material"));
	UMaterialInterface* MaterialB = LoadObject<UMaterialInterface>(NULL, TEXT("/Script/Engine.Material'/Game/Demo_5_1/Material/MaterialB_BP.MaterialB_BP'"));

	if (AMyCube* CubeM = Cast<AMyCube>(CubeInstan))
	{
		CubeM->SetMate(0, MaterialB);
	}
}

void ACollisionActor::SetMyWidgetInstance(USplineUserWidget* _MyWidgetInstance)
{
	this->MyWidgetInstance = _MyWidgetInstance;
}

void ACollisionActor::DestroyeSpawnedActor()
{
	if (UI3DIntance)
	{
		UI3DIntance->Destroy();
		UI3DIntance = nullptr;
	}
	
	if (CubeInstan)
	{
		CubeInstan->Destroy();
		CubeInstan = nullptr;
	}
}
