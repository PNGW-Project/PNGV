#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraTestTarget.generated.h"

/**
 * Простой объект-ориентир для тестирования камеры
 */
UCLASS()
class FIRST_API ACameraTestTarget : public AActor
{
    GENERATED_BODY()

public:
    ACameraTestTarget();
};