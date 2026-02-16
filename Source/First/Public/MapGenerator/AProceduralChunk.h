#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralChunk.generated.h"

/*
 Отвечает за:
*Генерацию terrain mesh
*Построение вершин через noise
*Создание ProceduralMesh 
*/
class FIRST_API AProceduralChunk : public AActor
{
public:
	AProceduralChunk();
	~AProceduralChunk();
	void GenerateChunk(int32 ChunkX, int32 ChunkY, int32 Seed);

protected:
    UPROPERTY(VisibleAnywhere)
    UProceduralMeshComponent* Mesh;

private:
    int32 ChunkSize = 2000;
    int32 VerticesPerLine = 100;
    float HeightMultiplier = 300.f;

    float GetHeight(float WorldX, float WorldY, int32 Seed) const;
};
