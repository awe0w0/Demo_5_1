// Fill out your copyright notice in the Description page of Project Settings.


#include "UI3D.h"

#include "UserWidget3D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AUI3D::AUI3D()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UI3DCom = CreateDefaultSubobject<UWidgetComponent>("UI3DCom");
	UI3DCom->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AUI3D::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUI3D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APlayerCameraManager* MPawnCameraManager = Cast<APlayerCameraManager>(GetWorld()->GetFirstPlayerController()->PlayerCameraManager);
	
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(UI3DCom->GetComponentLocation(), MPawnCameraManager->GetCameraLocation());


	//UI3DCom->SetRelativeLocation(Loc);
	UI3DCom->SetWorldRotation(Rot);
	
	float Distance = FVector::Dist(MPawnCameraManager->GetCameraLocation(), GetActorLocation());
	FString SDis = FString::Printf(TEXT("%.2f"), Distance);
	Cast<UUserWidget3D>(UI3DCom->GetUserWidgetObject())->DistanceToPawn->SetText(FText::FromString(SDis));

	//if ((Cast<AMyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->SholdDestory)) Destroy();

}

