#include "Camera/Perspective/Components/CameraZoomComponent.h"

#include "Camera/Perspective/PerspectiveCameraPawn.h"
#include "Camera/Perspective/PerspectiveCameraSettings.h"
#include "GameFramework/SpringArmComponent.h"

UCameraZoomComponent::UCameraZoomComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCameraZoomComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCameraZoomComponent::AddZoom(float Value)
{
    ZoomVelocity += Value * 1500.f;
}

void UCameraZoomComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    APerspectiveCameraPawn* Pawn =
        Cast<APerspectiveCameraPawn>(GetOwner());

    if (!Pawn || !Pawn->Settings) return;

    float& ArmLength = Pawn->SpringArm->TargetArmLength;

    ArmLength = FMath::Clamp(
        ArmLength - ZoomVelocity * DeltaTime,
        Pawn->Settings->MinZoom,
        Pawn->Settings->MaxZoom
    );

    // демпфирование
    ZoomVelocity = FMath::FInterpTo(
        ZoomVelocity, 0.f, DeltaTime, 5.f
    );
}
