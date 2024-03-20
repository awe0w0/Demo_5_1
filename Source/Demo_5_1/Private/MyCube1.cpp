// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCube1.h"

#include "MyCube.h"
#include "MyDefaultPawn.h"
#include "Components/SplineComponent.h"

// Sets default values
AMyCube1::AMyCube1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>("Cube");
	RootComponent = Cube;
}

// Called when the game starts or when spawned
void AMyCube1::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->GetTimerManager().SetTimer(TH, this, &AMyCube1::DestroySelf, 30.f);
}

void AMyCube1::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Cube1 Hited"));
	if (InstigatorPawn)
	{
		Cast<AMyDefaultPawn>(InstigatorPawn)->DestroySpline();
	}else UE_LOG(LogTemp, Log, TEXT("No Pawn"));
}

// Called every frame
void AMyCube1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCube1::DestroySelf()
{
	Destroy();
}

inline void AMyCube1::SetMate(int32 ElementIndex, UMaterialInterface* Material)
{
	Cube->SetMaterial(ElementIndex,Material);
}

inline void AMyCube1::SetCollision(ECollisionEnabled::Type NewType)
{
	Cube->SetCollisionEnabled(NewType);
}
