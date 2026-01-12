#include "World/Debug/CameraTestTarget.h"
#include "Components/StaticMeshComponent.h"

ACameraTestTarget::ACameraTestTarget()
{
    UStaticMeshComponent* Mesh =
        CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    RootComponent = Mesh;
}