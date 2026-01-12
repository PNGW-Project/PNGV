#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraZoomComponent.generated.h"

/**
 * Компонент зума с инерцией
 */
UCLASS(ClassGroup = (Camera), meta = (BlueprintSpawnableComponent))
class FIRST_API UCameraZoomComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCameraZoomComponent();

    void AddZoom(float Value);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;

private:
    float ZoomVelocity = 0.f;
};
