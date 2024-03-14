// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "GameFramework/Actor.h"
#include "MyCube1.generated.h"

UCLASS()
class DEMO_5_1_API AMyCube1 : public AActor, public IMyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCube1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact_Implementation(APawn* InstigatorPawn);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cube;

	UPROPERTY()
	FTimerHandle TH;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroySelf();

	void SetMate(int32 ElementIndex, UMaterialInterface* Material);

	void SetCollision(ECollisionEnabled::Type NewType);
};
