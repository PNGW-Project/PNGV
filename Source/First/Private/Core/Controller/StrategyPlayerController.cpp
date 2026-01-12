#include "Core/Controller/StrategyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Camera/Perspective/PerspectiveCameraPawn.h"
#include "Camera/Perspective/Components/CameraMoveComponent.h"
#include "Camera/Perspective/Components/CameraZoomComponent.h"
#include "Camera/Perspective/Components/CameraRotateComponent.h"

void AStrategyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (auto* Subsystem =
            LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(CameraMapping, 0);
        }
    }
}

void AStrategyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EIC =
        Cast<UEnhancedInputComponent>(InputComponent);

    if (!EIC) return;

    EIC->BindAction(IA_Move, ETriggerEvent::Triggered,
        this, &AStrategyPlayerController::OnMove);

    EIC->BindAction(IA_Zoom, ETriggerEvent::Triggered,
        this, &AStrategyPlayerController::OnZoom);

    EIC->BindAction(IA_Rotate, ETriggerEvent::Triggered,
        this, &AStrategyPlayerController::OnRotate);
}

void AStrategyPlayerController::OnMove(const FInputActionValue& Value)
{
    APerspectiveCameraPawn* Cam =
        Cast<APerspectiveCameraPawn>(GetPawn());
    if (!Cam) return;

    FVector2D Axis = Value.Get<FVector2D>();

    Cam->MoveComponent->Move(
        Cam->GetActorForwardVector(), Axis.Y);

    Cam->MoveComponent->Move(
        Cam->GetActorRightVector(), Axis.X);
}

void AStrategyPlayerController::OnZoom(const FInputActionValue& Value)
{
    APerspectiveCameraPawn* Cam =
        Cast<APerspectiveCameraPawn>(GetPawn());
    if (!Cam) return;

    Cam->ZoomComponent->AddZoom(Value.Get<float>());
}

void AStrategyPlayerController::OnRotate(const FInputActionValue& Value)
{
    APerspectiveCameraPawn* Cam =
        Cast<APerspectiveCameraPawn>(GetPawn());
    if (!Cam) return;

    Cam->RotateComponent->Rotate(Value.Get<float>());
}