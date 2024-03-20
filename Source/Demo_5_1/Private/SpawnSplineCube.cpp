// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSplineCube.h"

#include "SplineUserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnSplineCube::ASpawnSplineCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>("Cube");
	RootComponent = Cube;
	
}

// Called when the game starts or when spawned
void ASpawnSplineCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnSplineCube::Interact_Implementation(APawn* InstigatorPawn)
{
	IMyInterface::Interact_Implementation(InstigatorPawn);
	
	if (Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->SplineDestroyed) {

		if (SplineActor) SplineActor->Destroy();
		
		TMap<int64, FUserState> JsonMap = (Cast<AJsonRequest>(UGameplayStatics::GetActorOfClass(GetWorld(), AJsonRequest::StaticClass())))->JsonMap;
		
		TArray<FVector> Locations;
		for (TPair<int64, FUserState> State : JsonMap)
		{
			Locations.Push(FVector(State.Value.P.O.X, State.Value.P.O.Y, State.Value.P.O.Z));
		}
		FRotator Rotator = FRotator(0,0,0);
	
		SplineActor = Cast<AMySpline>(GetWorld()->SpawnActor<AActor>(MySpline, FTransform(Rotator, FVector(0,0,0))));

		SplineActor->Spline->ClearSplinePoints();
		
		for (FVector Location : Locations) {
			SplineActor->Spline->AddSplinePoint(Location, ESplineCoordinateSpace::World);
		}

		if (Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->Cube1Instan)
			Cast<AMyCube1>(Cast<AMyDefaultPawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->Cube1Instan)->SetCollision(ECollisionEnabled::QueryAndPhysics);
		
	}
}

// Called every frame
void ASpawnSplineCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnSplineCube::SetMate(int32 ElementIndex, UMaterialInterface* Material)
{
	Cube->SetMaterial(ElementIndex,Material);
}

