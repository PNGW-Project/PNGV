#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PerspectiveCameraSettings.generated.h"

/**
 * DataAsset с настройками перспективной RTS-камеры
 * Не содержит логики — только данные
 */
UCLASS()
class FIRST_API UPerspectiveCameraSettings : public UDataAsset
{
    GENERATED_BODY()

public:
    // Зум
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MinZoom = 800.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MaxZoom = 3000.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ZoomSpeed = 1500.f;

    // Движение
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MoveSpeed = 3500.f;

    // Поворот
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float RotationSpeed = 90.f;

    // Наклон камеры
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float PitchAngle = -30.f;
};
