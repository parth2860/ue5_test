// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ue5_fps_boxGameMode.generated.h"

UCLASS(minimalapi)
class Aue5_fps_boxGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	Aue5_fps_boxGameMode();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    // Timer handle for spawning boxes
    FTimerHandle SpawnTimerHandle;

};

	





