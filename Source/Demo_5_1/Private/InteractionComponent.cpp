// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "MyInterface.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionComponent::PrimaryInteract() const
{
	UE_LOG(LogTemp, Log, TEXT("Primary Interact"));
	//碰撞查询参数
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* MyOwner = GetOwner();

	//获取视线位置和实现方向并存为左值

	APlayerCameraManager* MPawnCameraManager = Cast<APlayerCameraManager>(GetWorld()->GetFirstPlayerController()->PlayerCameraManager);

	FVector EyeLocation = MPawnCameraManager->GetCameraLocation();
	FRotator EyeRotation = MPawnCameraManager->GetCameraRotation();

	//能击打到actor的长度
	FVector End = EyeLocation + (EyeRotation.Vector() * 10000);

	//向视线方向击打actor并获取是否击打到
	FHitResult Hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		//击打到后检测是否为UMyInterface类
		if (HitActor->Implements<UMyInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			//执行互动
			IMyInterface::Execute_Interact(HitActor, MyPawn);
		}
	}

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	//debug线
	EyeLocation += EyeRotation.Vector() * 30;
	
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 30.0f, 0, 2.0f);
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

