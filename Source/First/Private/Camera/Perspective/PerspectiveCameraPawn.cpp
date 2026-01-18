#include "Camera/Perspective/PerspectiveCameraPawn.h"
#include "Camera/Perspective/PerspectiveCameraSettings.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/Perspective/Components/CameraMoveComponent.h"
#include "Camera/Perspective/Components/CameraZoomComponent.h"
#include "Camera/Perspective/Components/CameraRotateComponent.h"

APerspectiveCameraPawn::APerspectiveCameraPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>("Root");
    RootComponent = Root;

    Pivot = CreateDefaultSubobject<USceneComponent>("Pivot");
    Pivot->SetupAttachment(Root);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(Pivot);
    SpringArm->bDoCollisionTest = false;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);

    // Логика вынесена в компоненты
    MoveComponent = CreateDefaultSubobject<UCameraMoveComponent>("MoveComponent");
    ZoomComponent = CreateDefaultSubobject<UCameraZoomComponent>("ZoomComponent");
    RotateComponent = CreateDefaultSubobject<UCameraRotateComponent>("RotateComponent");
}

void APerspectiveCameraPawn::BeginPlay()
{
    Super::BeginPlay();

    if (!Settings) return;

    SpringArm->TargetArmLength = Settings->MaxZoom;
    SpringArm->SetRelativeRotation(FRotator(Settings->PitchAngle, 0.f, 0.f));
}

void APerspectiveCameraPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (MoveComponent)
    {
        MoveComponent->EdgeScroll();
    }
}
