#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebugWorldActor.generated.h"

/**
 * Debug-Actor для визуализации мира и камеры.
 * НЕ участвует в геймплее.
 * Используется только в debug / editor картах.
 */
UCLASS()
class FIRST_API ADebugWorldActor : public AActor
{
    GENERATED_BODY()

public:
    ADebugWorldActor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    // ===== Debug toggles =====

    // Рисовать мировую сетку
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bDrawWorldGrid = true;

    // Размер сетки
    UPROPERTY(EditAnywhere, Category = "Debug")
    float GridSize = 10000.f;

    // Шаг сетки
    UPROPERTY(EditAnywhere, Category = "Debug")
    float GridStep = 1000.f;

    // Показывать pivot камеры
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bDrawCameraPivot = true;
};
