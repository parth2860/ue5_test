// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue5_fps_boxGameMode.h"
#include "ue5_fps_boxCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
//#include "cp_box.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

Aue5_fps_boxGameMode::Aue5_fps_boxGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
// Called when the game starts or when spawned
void Aue5_fps_boxGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Set up the timer to call function every 10 seconds
	//GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &Aue5_fps_boxGameMode::spawnbox, 10.0f, true);
}




