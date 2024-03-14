// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpline.h"

#include "CollisionActor.h"
#include "CubeWithCamera.h"
#include "Kismet/GameplayStatics.h"

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

	SLength = Spline->GetSplineLength();
	
	//Cast<USplineUserWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), USplineUserWidget::StaticClass()))->SetSplineActor(this);
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

	AMyDefaultPawn* DefaultPawn = Cast<AMyDefaultPawn>(MyPawn);
	DefaultPawn->SetFOV(90);
				
	DefaultPawn->CreateCube1();
}

// Called every frame
void AMySpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DefaultPawn = Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (Spline && !DefaultPawn->SplineDestroyed) {
		if(PIsPawnMoving) {
			if (!Goback)
			{
				FVector NewLoc = Spline->GetLocationAtDistanceAlongSpline(Current, ESplineCoordinateSpace::Type::World);
				FRotator NewRot = Spline->GetRotationAtDistanceAlongSpline(Current, ESplineCoordinateSpace::Type::World); 
	
				DefaultPawn->SetActorLocation(NewLoc);
				DefaultPawn->Controller->SetControlRotation(NewRot);
			
				Current += Speed / (1 / DeltaTime);

				if (Current >= SLength)
				{
					bSplineDone = true;
					//Current = 0.f;
					//CurrentRot = Spline->GetRotationAtDistanceAlongSpline(SLength, ESplineCoordinateSpace::Type::Local);
					Goback = true;
					ViewBlandStart = true;
				}
			}
			else 
			{
				if (ViewBlandStart) {
					APawn* MyPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
					AActor* ACamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACubeWithCamera::StaticClass());
					GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(ACamera, 1.f);
					if (bSplineDone)
					{
						GetWorld()->GetTimerManager().SetTimer(TH, this, &AMySpline::SplineDone ,1.f);
						bSplineDone = false;
					}
				}
				
			}
		}
	}
	
}

