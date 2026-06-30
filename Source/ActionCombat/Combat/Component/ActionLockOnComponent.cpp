
#include "ActionLockOnComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UActionLockOnComponent::UActionLockOnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}




// Called when the game starts
void UActionLockOnComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerRef = GetOwner<ACharacter>();

	if (OwnerRef)
	{
		CharacterMovementRef = OwnerRef->GetCharacterMovement();
		ControllerRef = Cast<APlayerController>(OwnerRef->GetController());
	}
	
}

void UActionLockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UActionLockOnComponent::StartLockOn()
{
	FHitResult HitResult;
	FVector CurrentLocation=GetOwner()->GetActorLocation();
	FCollisionShape Sphere=FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams CollisionParams=FCollisionQueryParams(FName("Sphere"),false,GetOwner());
	bool bHasFoundTarget (GetWorld()->SweepSingleByChannel(HitResult,CurrentLocation,CurrentLocation,FQuat::Identity,ECC_GameTraceChannel1,Sphere,CollisionParams));
	
	if (bHasFoundTarget)
	{
		ControllerRef->SetIgnoreLookInput(true);
		CharacterMovementRef->bOrientRotationToMovement=false;
		CharacterMovementRef->bUseControllerDesiredRotation=true;
		
	}
	
}
