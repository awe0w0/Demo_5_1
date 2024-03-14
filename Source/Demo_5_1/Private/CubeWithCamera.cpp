// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeWithCamera.h"

// Sets default values
ACubeWithCamera::ACubeWithCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACubeWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

