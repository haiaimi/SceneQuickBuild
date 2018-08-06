// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/PlatformController.h"
#include "FlightPlatform.h"
#include "Engine/World.h"
#include "OriginHelper.h"

// Sets default values
APlatformController::APlatformController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlatformController::BeginPlay()
{
	Super::BeginPlay();
	ControlPlatform = GetWorld()->SpawnActor<AFlightPlatform>(FVector(-225.f, 0.f, 17454.f), FRotator(0.f,0.f,0.f));
	if (ControlPlatform)
	{
		Possess(ControlPlatform);
		ControlPlatform->SetPlatformData(TEXT("Plane_1"), ESQBTeam::EPlayer);

		if (USQBGameInstance* GameInstance = Cast<USQBGameInstance>(GetGameInstance()))
		{
			GameInstance->RegisterSQBActor(ControlPlatform);
		}

		UFunction* test = ControlPlatform->GetClass()->FindFunctionByName(TEXT("EventTest"));

		if (test)
		{
			struct Param
			{
				float Speed;
				int32 Num;
				int32 Return;
				FVector Pos;
			};

			Param params;
			params.Speed = 500.f;
			params.Num = 10;
			params.Pos = FVector(10.f, 10.f, 10.f);

			float* a = (float*)(&params);
			OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(*a),5);
			int32* b = (int32*)(++a);
			OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(*b),5);
			FVector* Pos = (FVector*)(++a);
			OriginHelper::Debug_ScreenMessage(Pos->ToString());
			//void* param1 = nullptr;
			//FFrame* Frame = new FFrame(ControlPlatform, test, &params);
			//ControlPlatform->CallFunction(*Frame, &params, test);
			//ControlPlatform->ProcessEvent(test, (void*)(&params));
			test->GetOuter()->ProcessEvent(test, (void*)(&params));
			//OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(params.Return));
			//delete Frame;

			FMessagePublish Publisher;
		}
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	TArray<FName> Result = ControlPlatform->GetData_AllOtherName();
	for (auto Iter = TArray<FName>::TIterator(Result); Iter; ++Iter)
	{
		//OriginHelper::Debug_ScreenMessage((*Iter).ToString());
	}
}

// Called every frame
void APlatformController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding ActionBinding(TEXT("ScreenLog"), EInputEvent::IE_Pressed);
	//ActionBinding.ActionDelegate.BindDelegate(ControlPlatform, &AFlightPlatform::EventTest);
	
	if (InputComponent)
	{
		InputComponent->BindAction(TEXT("Quit"), EInputEvent::IE_Pressed, this, &APlatformController::Quit);
	}
}

void APlatformController::EventTest()
{
	OriginHelper::Debug_ScreenMessage(TEXT("Event Touched"));
}

void APlatformController::Quit()
{
	ConsoleCommand("quit");
}
