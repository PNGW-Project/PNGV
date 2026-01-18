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
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

public:
    // ===== Settings =====
    UPROPERTY(EditAnywhere, Category = "Camera")
    UPerspectiveCameraSettings* Settings;

    // ===== Scene =====
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USceneComponent* Pivot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* Camera;

    // ===== Logic components =====
    UPROPERTY(VisibleAnywhere)
    UCameraMoveComponent* MoveComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraZoomComponent* ZoomComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraRotateComponent* RotateComponent;
};
