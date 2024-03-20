// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/DefaultPawn.h"
#include "InteractionComponent.h"
#include "GameFramework/Pawn.h"
#include "MyDefaultPawn.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_5_1_API AMyDefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()

	friend class USplineUserWidget;

	friend class AUI3D;

public:
	// Sets default values for this pawn's properties
	AMyDefaultPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Cube1;


	FRotator CurrentRot;

	void PrimaryInteract();

public:
	// Called every frame
    virtual void Tick(float DeltaTime) override;
   
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	USplineUserWidget* MyWidgetInstance;

	UPROPERTY()
	AActor* Cube1Instan;

	bool SplineDestroyed;

	void DestroySpline();

	void SetFOV(float FOV);

	void CreateCube1();

	TSharedPtr<FJsonObject> Json;
};
