#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator/AProceduralChunk.h"
#include "AWorldGenerator.generated.h"

UCLASS()
class FIRST_API AWorldGenerator : public AActor
{
    GENERATED_BODY()

public:
    AWorldGenerator();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    int32 Seed = 12345;

    UPROPERTY(EditAnywhere)
    int32 ChunkSize = 2000;

    UPROPERTY(EditAnywhere)
    int32 RenderDistance = 2;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AProceduralChunk> ChunkClass;

private:
    TMap<FIntPoint, AProceduralChunk*> ActiveChunks;

    void UpdateChunks();
};