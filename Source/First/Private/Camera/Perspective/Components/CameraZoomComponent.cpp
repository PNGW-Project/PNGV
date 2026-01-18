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

    float Alpha = FMath::GetMappedRangeValueClamped(
        FVector2D(Pawn->Settings->MinZoom, Pawn->Settings->MaxZoom),
        FVector2D(1.f, 0.f),
        ArmLength
    );

    float Pitch = FMath::Lerp(
        Pawn->Settings->MinPitch,
        Pawn->Settings->MaxPitch,
        Alpha
    );

    Pawn->SpringArm->SetRelativeRotation(
        FRotator(Pitch, 0.f, 0.f)
    );

    // демпфирование
    ZoomVelocity = FMath::FInterpTo(
        ZoomVelocity, 0.f, DeltaTime, 5.f
    );
}
