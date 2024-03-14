// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SplineUserWidget.h"
#include "CollisionActor.generated.h"

UCLASS()
class DEMO_5_1_API ACollisionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollisionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;
	
	USplineUserWidget* MyWidgetInstance;

	UPROPERTY(VisibleAnywhere)
	AActor* UI3DIntance;

	UPROPERTY()
	AActor* CubeInstan;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> UI3D;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Cube;

	UPROPERTY()
	FTimerHandle TH;

	UPROPERTY()
	FTimerHandle TH1;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Create3DUI();
	
	void CreateCube();

	void SetButtonColor();
	
	void ButtonBImageAndCameraFOV();

	UFUNCTION()
	void SetCubeMaterial();

	void SetMyWidgetInstance(USplineUserWidget* MyWidgetInstance);

	void DestroyeSpawnedActor();
};
