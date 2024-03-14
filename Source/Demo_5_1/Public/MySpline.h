// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCube1.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "MyDefaultPawn.h"
#include "MySpline.generated.h"

UCLASS()
class DEMO_5_1_API AMySpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Cube1;
	
	AMyDefaultPawn* DefaultPawn;

	FTimerHandle TH;
	
	float Current;

	float SLength;
	
	bool Goback;

	bool ViewBlandStart;

	bool bSplineDone;
	
	void SplineDone();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* Cube1Instan;

	UPROPERTY(EditAnywhere)
	float Speed;

	bool PIsPawnMoving;

	UPROPERTY(VisibleAnywhere)
	USplineComponent* Spline;
};
