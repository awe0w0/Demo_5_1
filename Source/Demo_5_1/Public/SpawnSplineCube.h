// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "GameFramework/Actor.h"
#include "JsonRequest.h"
#include "MySpline.h"
#include "SpawnSplineCube.generated.h"

UCLASS()
class DEMO_5_1_API ASpawnSplineCube : public AActor, public IMyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnSplineCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cube;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMySpline> MySpline;

	AMySpline* SplineActor;
	
	bool SplineSpawned = false;
	
	void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetMate(int32 ElementIndex, UMaterialInterface* Material);

};
