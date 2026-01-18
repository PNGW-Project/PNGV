#include "Camera/Perspective/Components/CameraMoveComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Camera/Perspective/PerspectiveCameraPawn.h"
#include "Camera/Perspective/PerspectiveCameraSettings.h"

void UCameraMoveComponent::Move(const FVector& Direction, float Value)
{
    if (Value == 0.f) return;

    APawn* Pawn = Cast<APawn>(GetOwner());
    if (!Pawn) return;

    Pawn->AddActorWorldOffset(
        Direction * Value * 3500.f * GetWorld()->DeltaTimeSeconds,
        true
    );

    FVector Loc = Pawn->GetActorLocation();
    const auto* Settings = Cast<APerspectiveCameraPawn>(Pawn)->Settings;

    Loc.X = FMath::Clamp(Loc.X, Settings->WorldMin.X, Settings->WorldMax.X);
    Loc.Y = FMath::Clamp(Loc.Y, Settings->WorldMin.Y, Settings->WorldMax.Y);

    Pawn->SetActorLocation(Loc);
}

void UCameraMoveComponent::EdgeScroll()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    float MouseX, MouseY;
    int32 SizeX, SizeY;
    PC->GetMousePosition(MouseX, MouseY);
    PC->GetViewportSize(SizeX, SizeY);

    const float Edge = 20.f;
    FVector Dir = FVector::ZeroVector;

    if (MouseX < Edge) Dir -= PC->GetPawn()->GetActorRightVector();
    if (MouseX > SizeX - Edge) Dir += PC->GetPawn()->GetActorRightVector();
    if (MouseY < Edge) Dir += PC->GetPawn()->GetActorForwardVector();
    if (MouseY > SizeY - Edge) Dir -= PC->GetPawn()->GetActorForwardVector();

    if (!Dir.IsZero())
    {
        PC->GetPawn()->AddActorWorldOffset(
            Dir.GetSafeNormal() * 2000.f * GetWorld()->DeltaTimeSeconds
        );
    }
}

