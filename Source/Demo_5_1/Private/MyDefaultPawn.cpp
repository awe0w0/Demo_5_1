// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"

#include "CollisionActor.h"
#include "InteractionComponent.h"
#include "MyCube1.h"
#include "Kismet/GameplayStatics.h"
#include "SlateCore/Public/Styling/SlateTypes.h"

// Sets default values
AMyDefaultPawn::AMyDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = Super::GetCollisionComponent();

	InteractionComp = CreateDefaultSubobject<UInteractionComponent>("InteractionComp");

	SplineDestroyed = false;
}

// Called when the game starts or when spawned
void AMyDefaultPawn::BeginPlay()
{
	Super::BeginPlay();

	if (MyWidgetInstance)
	{
		MyWidgetInstance->RemoveFromViewport();
		MyWidgetInstance = nullptr;
	}
	
	if (UClass* MyWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Demo_5_1/SplineUserWidget_BP.SplineUserWidget_BP_C'")))
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			MyWidgetInstance = Cast<USplineUserWidget>(CreateWidget<UUserWidget>(PC, MyWidgetClass));
			if (MyWidgetInstance)
			{
				MyWidgetInstance->AddToViewport();
				Cast<ACollisionActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACollisionActor::StaticClass()))->SetMyWidgetInstance(MyWidgetInstance);
			}
		}
	}
	
}




// Called every frame
void AMyDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Loc = GetActorLocation();
	FString StL = FString::Printf(TEXT("%.2f, %.2f, %.2f"), Loc.X, Loc.Y, Loc.Z);
	MyWidgetInstance->SetLocationText(FText::FromString(StL));
	
	FRotator Rot = GetControlRotation();
	FString StR = FString::Printf(TEXT("%.2f, %.2f, %.2f"), Rot.Roll, Rot.Pitch, Rot.Yaw);
	MyWidgetInstance->SetRotationText(FText::FromString(StR));
}

// Called to bind functionality to input
void AMyDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMyDefaultPawn::PrimaryInteract);
}

void AMyDefaultPawn::PrimaryInteract()
{
	if (InteractionComp)
	{
		UE_LOG(LogTemp, Log, TEXT("Primary Interact"));
		InteractionComp->PrimaryInteract();
	}
}

void AMyDefaultPawn::DestroySpline()
{
 	Cast<AMyCube1>(Cube1Instan)->SetCollision(ECollisionEnabled::NoCollision);

	Cast<AMySpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMySpline::StaticClass()))->Destroy();
	
	SplineDestroyed = true;
	
}

void AMyDefaultPawn::SetFOV(float FOV)
{
	Cast<APlayerController>(GetController())->PlayerCameraManager->SetFOV(FOV);
}

void AMyDefaultPawn::CreateCube1()
{
	FVector Loc = Cast<AMySpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMySpline::StaticClass()))->Spline->GetLocationAtTime(0.f, ESplineCoordinateSpace::Type::World);
	Loc.X += 500;
	Loc.Y -= 700;
	Loc.Z -= 200;

	Cube1Instan = GetWorld()->SpawnActor<AActor>(Cube1, FTransform(GetActorRotation(), Loc));

	UMaterialInterface* MaterialB = LoadObject<UMaterialInterface>(NULL, TEXT("/Script/Engine.Material'/Game/Demo_5_1/Material/MaterialB_BP.MaterialB_BP'"));

	if (AMyCube1* Cube1 = Cast<AMyCube1>(Cube1Instan))
	{
		Cube1->SetMate(0, MaterialB);
	}
}
