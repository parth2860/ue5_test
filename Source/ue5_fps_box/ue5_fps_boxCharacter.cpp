// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue5_fps_boxCharacter.h"
#include "ue5_fps_boxProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "cp_data_2.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ui_widget.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// Aue5_fps_boxCharacter

Aue5_fps_boxCharacter::Aue5_fps_boxCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Set default values
	//ScoreWidgetClass = nullptr;
	//ScoreWidget = nullptr;
	/*
	// Set default widget class (path must match your project structure)
	//static ConstructorHelpers::FClassFinder<Uui_widget> WidgetClassFinder(TEXT("Game/FirstPerson/Blueprints/bp_ui_widget.bp_ui_widget_C"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/FirstPerson/Blueprints/bp_ui_widget.bp_ui_widget_C"));
	///Game/FirstPerson/Blueprints/bp_ui_widget.bp_ui_widget//object path
	///Script/UMGEditor.WidgetBlueprint'/Game/FirstPerson/Blueprints/bp_ui_widget.bp_ui_widget'//copy refernce
	////Game/FirstPerson/Blueprints/bp_ui_widget.bp_ui_widget_C//
	if (WidgetClassFinder.Succeeded())
	{
		ScoreWidgetClass = WidgetClassFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find BP_ScoreWidget. Ensure the path is correct."));
	}*/
	// Assign the C++ class directly to ScoreWidgetClass
	ScoreWidgetClass = Uui_widget::StaticClass();

}

void Aue5_fps_boxCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the score widget
	InitializeScoreWidget();
}
//////////////////////////////////////////////////////////////////////////// Input

void Aue5_fps_boxCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void Aue5_fps_boxCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Aue5_fps_boxCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Aue5_fps_boxCharacter::Look);

		//spawn cube/box
		EnhancedInputComponent->BindAction(SpawnAction, ETriggerEvent::Started, this, &Aue5_fps_boxCharacter::Spawn);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void Aue5_fps_boxCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void Aue5_fps_boxCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void Aue5_fps_boxCharacter::Spawn(const FInputActionValue& Value)
{
	Acp_data_2* data = Cast<Acp_data_2>(UGameplayStatics::GetActorOfClass(GetWorld(), Acp_data_2::StaticClass()));

	data->ParseAndSpawnBoxes();
}
void Aue5_fps_boxCharacter::InitializeScoreWidget()
{
	if (ScoreWidgetClass)
	{
		// Create the widget
		ScoreWidget = CreateWidget<Uui_widget>(GetWorld(), ScoreWidgetClass);

		if (ScoreWidget)
		{
			// Add widget to the viewport
			ScoreWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("ScoreWidget added to viewport successfully."));

			// Optional: Ensure it's visible
			ScoreWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create ScoreWidget from ScoreWidgetClass."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreWidgetClass is not set."));
	}
}

// Called when Cube destroyed
void Aue5_fps_boxCharacter::UpdateScoreOnUI(int32 NewScore)
{
	if (ScoreWidget)
	{
		// Cast to your custom widget class to access specific functions
		if (Uui_widget* CustomWidget = Cast<Uui_widget>(ScoreWidget))
		{
			CustomWidget->UpdateScore(NewScore);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ScoreWidget is not of type Uui_widget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreWidget is not initialized"));
	}
}


