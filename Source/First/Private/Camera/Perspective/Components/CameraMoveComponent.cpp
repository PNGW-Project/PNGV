#include "Camera/Perspective/Components/CameraMoveComponent.h"
#include "GameFramework/Pawn.h"

void UCameraMoveComponent::Move(const FVector& Direction, float Value)
{
    if (Value == 0.f) return;

    APawn* Pawn = Cast<APawn>(GetOwner());
    if (!Pawn) return;

    Pawn->AddActorWorldOffset(
        Direction * Value * 3500.f * GetWorld()->DeltaTimeSeconds,
        true
    );
}
