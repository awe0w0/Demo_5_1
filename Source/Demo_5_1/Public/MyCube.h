// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCube.generated.h"

UCLASS()
class DEMO_5_1_API AMyCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cube;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SetMate(int32 ElementIndex, UMaterialInterface* Material);
};
