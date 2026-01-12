#include "World/Debug/DebugWorldActor.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/Perspective/PerspectiveCameraPawn.h"

ADebugWorldActor::ADebugWorldActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADebugWorldActor::BeginPlay()
{
    Super::BeginPlay();
}

void ADebugWorldActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

#if WITH_EDITOR

    UWorld* World = GetWorld();
    if (!World) return;

    // ===== World Grid =====
    if (bDrawWorldGrid)
    {
        for (float X = -GridSize; X <= GridSize; X += GridStep)
        {
            DrawDebugLine(
                World,
                FVector(X, -GridSize, 0.f),
                FVector(X, GridSize, 0.f),
                FColor::Green,
                false,
                -1.f,
                0,
                1.f
            );
        }

        for (float Y = -GridSize; Y <= GridSize; Y += GridStep)
        {
            DrawDebugLine(
                World,
                FVector(-GridSize, Y, 0.f),
                FVector(GridSize, Y, 0.f),
                FColor::Green,
                false,
                -1.f,
                0,
                1.f
            );
        }
    }

    // ===== Camera Pivot =====
    if (bDrawCameraPivot)
    {
        APawn* Pawn = UGameplayStatics::GetPlayerPawn(World, 0);
        APerspectiveCameraPawn* CameraPawn =
            Cast<APerspectiveCameraPawn>(Pawn);

        if (CameraPawn)
        {
            const FVector PivotLocation =
                CameraPawn->Pivot->GetComponentLocation();

            // Pivot sphere
            DrawDebugSphere(
                World,
                PivotLocation,
                50.f,
                16,
                FColor::Red,
                false,
                -1.f,
                0,
                2.f
            );

            // Forward vector
            DrawDebugLine(
                World,
                PivotLocation,
                PivotLocation + CameraPawn->GetActorForwardVector() * 300.f,
                FColor::Blue,
                false,
                -1.f,
                0,
                3.f
            );

            // Right vector
            DrawDebugLine(
                World,
                PivotLocation,
                PivotLocation + CameraPawn->GetActorRightVector() * 300.f,
                FColor::Yellow,
                false,
                -1.f,
                0,
                3.f
            );
        }
    }

#endif // WITH_EDITOR
}
