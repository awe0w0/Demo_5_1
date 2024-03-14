// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "UI3D.generated.h"

UCLASS()
class DEMO_5_1_API AUI3D : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUI3D();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* UI3DCom;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
