#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PerspectiveCameraPawn.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UPerspectiveCameraSettings;

class UCameraMoveComponent;
class UCameraZoomComponent;
class UCameraRotateComponent;

/**
 * Pawn камеры (RTS / Strategy)
 * Сам не обрабатывает input — только принимает команды
 */

UCLASS()
class FIRST_API APerspectiveCameraPawn : public APawn
{
    GENERATED_BODY()

public:
    APerspectiveCameraPawn();

protected:
    virtual void BeginPlay() override;

public:
    // ===== Settings =====
    UPROPERTY(EditAnywhere, Category = "Camera")
    UPerspectiveCameraSettings* Settings;

    // ===== Scene =====
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Pivot;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    // ===== Logic components =====
    UPROPERTY(VisibleAnywhere)
    UCameraMoveComponent* MoveComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraZoomComponent* ZoomComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraRotateComponent* RotateComponent;
};
