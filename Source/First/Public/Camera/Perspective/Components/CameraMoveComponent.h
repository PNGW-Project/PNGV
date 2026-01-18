#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraMoveComponent.generated.h"

/**
 * Компонент движения камеры в плоскости мира
 */
UCLASS(ClassGroup = (Camera), meta = (BlueprintSpawnableComponent))
class FIRST_API UCameraMoveComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void Move(const FVector& Direction, float Value);
    void EdgeScroll();
};
