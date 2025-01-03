// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_cube.h"
#include "ue5_fps_boxCharacter.h"
#include "Kismet/GameplayStatics.h"

// Static score variable
int32 Acp_cube::TotalScore = 0;

// Sets default values
Acp_cube::Acp_cube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and attach the StaticMeshComponent to the actor
    BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
    RootComponent = BoxMesh;

    // Load the mesh asset
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (BoxMeshAsset.Succeeded())
    {
        BoxMesh->SetStaticMesh(BoxMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load static mesh for BoxMesh. Check the asset path."));
    }

    // Default values
    CubeHealth = 0;
    CubeScore = 0;

}

// Called when the game starts or when spawned
void Acp_cube::BeginPlay()
{
	Super::BeginPlay();

    Acp_cube::TotalScore = 0;

}

// Called every frame
void Acp_cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Initialize the box properties using data from the JSON
void Acp_cube::InitializeBox(FString Type, FVector Location, FRotator Rotation, FVector Scale, FLinearColor Color, int32 Health, int32 Score)
{
   
    // Apply material color
    BoxMaterial = UMaterialInstanceDynamic::Create(BoxMesh->GetMaterial(0), this);
    BoxMesh->SetMaterial(0, BoxMaterial);
    BoxMaterial->SetVectorParameterValue("BaseColor", Color);

    // Use this->to refer to the member variables
    this->CubeType = Type;
    this->CubeLocation = Location;
    this->CubeRotation = Rotation;
    this->CubeScale = Scale;
    this->CubeColor = Color;
    this->CubeHealth = Health;
    this->CubeScore = Score;

    // Set up cube actor properties based on this data
    SetActorLocation(this->CubeLocation);
    SetActorRotation(this->CubeRotation);
    SetActorScale3D(this->CubeScale);

    // Apply material color
    BoxMaterial = UMaterialInstanceDynamic::Create(BoxMesh->GetMaterial(0), this);
    BoxMesh->SetMaterial(0, BoxMaterial);
    BoxMaterial->SetVectorParameterValue("BaseColor", Color);

    
    // Set Material Color based on CubeColor
    UMaterial* BaseMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/FirstPerson/Blueprints/BaseColorMaterial.BaseColorMaterial"));
    if (BaseMaterial)
    {
        // Reload the material to ensure it is fully initialized
        BaseMaterial->MarkPackageDirty();
        BaseMaterial->PostEditChange();

        // Now proceed with creating the dynamic material
        UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
        if (MaterialInstance)
        {
            MaterialInstance->SetVectorParameterValue(TEXT("BaseColor"), CubeColor);
            BoxMesh->SetMaterial(0, MaterialInstance);
            UE_LOG(LogTemp, Warning, TEXT("Dynamic material applied successfully with color: %s"), *CubeColor.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic material instance."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Base material not found."));
    }

}

// Apply damage to the box and reduce health
void Acp_cube::ApplyDamage()
{
    if (CubeHealth > 0)
    {
        CubeHealth -= 1;

        if (CubeHealth <= 0)
        {
            DestroyBox();
        }
    }
}

// Destroy the box and update the score
void Acp_cube::DestroyBox()
{
    TotalScore += CubeScore;

    // Get the player reference
    Aue5_fps_boxCharacter* PlayerReference = Cast<Aue5_fps_boxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (PlayerReference)
    {
        PlayerReference->UpdateScoreOnUI(TotalScore);
    }

    Destroy();
    UpdateScore();
}

void Acp_cube::UpdateScore()
{
    UE_LOG(LogTemp, Warning, TEXT("Total Score: %d"), TotalScore);
}
