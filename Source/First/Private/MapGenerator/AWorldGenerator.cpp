#include "MapGenerator/AWorldGenerator.h"
#include "Kismet/GameplayStatics.h"

AWorldGenerator::AWorldGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AWorldGenerator::BeginPlay()
{
    Super::BeginPlay();
}

void AWorldGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateChunks();
}

void AWorldGenerator::UpdateChunks()
{
    APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!Pawn) return;

    FVector Location = Pawn->GetActorLocation();

    int32 CurrentChunkX = FMath::FloorToInt(Location.X / ChunkSize);
    int32 CurrentChunkY = FMath::FloorToInt(Location.Y / ChunkSize);

    TSet<FIntPoint> NeededChunks;

    for (int32 x = -RenderDistance; x <= RenderDistance; x++)
    {
        for (int32 y = -RenderDistance; y <= RenderDistance; y++)
        {
            FIntPoint Coord(CurrentChunkX + x, CurrentChunkY + y);
            NeededChunks.Add(Coord);

            if (!ActiveChunks.Contains(Coord))
            {
                FVector SpawnLocation = FVector(
                    Coord.X * ChunkSize,
                    Coord.Y * ChunkSize,
                    0
                );

                AProceduralChunk* NewChunk = GetWorld()->SpawnActor<AProceduralChunk>(
                    ChunkClass,
                    SpawnLocation,
                    FRotator::ZeroRotator
                );

                if (NewChunk)
                {
                    NewChunk->GenerateChunk(Coord.X, Coord.Y, Seed);
                    ActiveChunks.Add(Coord, NewChunk);
                }
            }
        }
    }

    for (auto It = ActiveChunks.CreateIterator(); It; ++It)
    {
        if (!NeededChunks.Contains(It.Key()))
        {
            It.Value()->Destroy();
            It.RemoveCurrent();
        }
    }
}