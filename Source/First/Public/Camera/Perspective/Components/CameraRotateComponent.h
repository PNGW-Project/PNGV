#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraRotateComponent.generated.h"

/**
 * Компонент поворота камеры вокруг оси Z
 */
UCLASS(ClassGroup = (Camera), meta = (BlueprintSpawnableComponent))
class FIRST_API UCameraRotateComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void Rotate(float Value);
};
