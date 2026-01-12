#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "StrategyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * PlayerController для стратегии
 * Единственное место, где обрабатывается Input
 */
UCLASS()
class FIRST_API AStrategyPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    // ===== Enhanced Input =====
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* CameraMapping;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Move;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Zoom;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Rotate;

    // ===== Callbacks =====
    void OnMove(const FInputActionValue& Value);
    void OnZoom(const FInputActionValue& Value);
    void OnRotate(const FInputActionValue& Value);
};
