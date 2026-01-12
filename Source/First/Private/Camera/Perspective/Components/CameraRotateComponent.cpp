#include "Camera/Perspective/Components/CameraRotateComponent.h"
#include "GameFramework/Actor.h"

void UCameraRotateComponent::Rotate(float Value)
{
    if (Value == 0.f) return;

    AActor* Owner = GetOwner();
    if (!Owner) return;

    Owner->AddActorWorldRotation(
        FRotator(0.f, Value, 0.f)
    );
}
