// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ui_widget.generated.h"

/**
 * 
 */
 // Forward declarations
class UTextBlock;

UCLASS()
class UE5_FPS_BOX_API Uui_widget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// UI elements (TextBlocks or other UI elements)
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* ScoreText;

	// The text block for displaying the score (exposed for manual setup)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))//to extend used in blueprint
	// Score text reference
	UPROPERTY(meta = (BindWidget))//to used in cpp
	UTextBlock* ScoreText;

	// The function to update the score
	UFUNCTION( Category = "Score")
	void UpdateScore(int32 NewScore);

protected:
	
	// Native construct to initialize widget
	virtual void NativeConstruct() override;

private:
	// Variable to store the score value
	int32 CurrentScore;

};
