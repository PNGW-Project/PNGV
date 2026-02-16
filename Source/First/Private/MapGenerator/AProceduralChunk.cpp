#include "MapGenerator/AProceduralChunk.h"

/*
Отвечает за:
*Seed
*Размер чанка
*Радиус генерации
*Отслеживание позиции камеры
*Спавн / удаление чанков
*/

AProceduralChunk::AProceduralChunk()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
}

AProceduralChunk::~AProceduralChunk()
{
}

float AProceduralChunk::GetHeight(float WorldX, float WorldY, int32 Seed) const
{
    float Scale = 0.001f;
    return FMath::PerlinNoise2D(FVector2D(WorldX + Seed, WorldY + Seed) * Scale) * HeightMultiplier;
}

void AProceduralChunk::GenerateChunk(int32 ChunkX, int32 ChunkY, int32 Seed)
{
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FProcMeshTangent> Tangents;

    float Step = (float)ChunkSize / (VerticesPerLine - 1);

    for (int32 y = 0; y < VerticesPerLine; y++)
    {
        for (int32 x = 0; x < VerticesPerLine; x++)
        {
            float WorldX = ChunkX * ChunkSize + x * Step;
            float WorldY = ChunkY * ChunkSize + y * Step;

            float Z = GetHeight(WorldX, WorldY, Seed);

            Vertices.Add(FVector(x * Step, y * Step, Z));
            UVs.Add(FVector2D((float)x / VerticesPerLine, (float)y / VerticesPerLine));
            Normals.Add(FVector::UpVector);
            Tangents.Add(FProcMeshTangent(1, 0, 0));
        }
    }

    for (int32 y = 0; y < VerticesPerLine - 1; y++)
    {
        for (int32 x = 0; x < VerticesPerLine - 1; x++)
        {
            int32 i = x + y * VerticesPerLine;

            Triangles.Add(i);
            Triangles.Add(i + VerticesPerLine);
            Triangles.Add(i + 1);

            Triangles.Add(i + 1);
            Triangles.Add(i + VerticesPerLine);
            Triangles.Add(i + VerticesPerLine + 1);
        }
    }

    Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, {}, Tangents, true);
}

