// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformController.generated.h"

UCLASS()
class SCENEQUICKBUILD_API APlatformController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlatformController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupInputComponent()override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused);

	void EventTest();

	void Quit();

	void ToggleTarget();

	UFUNCTION()
	void PossessNewTarget();

private:
	class AFlightPlatform* ControlPlatform;

	/**在经过镜头转换后就开始Possess新目标*/
	FTimerHandle PossessHandle;
};
