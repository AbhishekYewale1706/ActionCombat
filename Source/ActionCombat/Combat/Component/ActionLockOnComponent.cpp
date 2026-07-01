
#include "ActionLockOnComponent.h"

#include "ActionCombat/Interface/ActionEnemy_Interface.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


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
		SpringArmRef=OwnerRef->FindComponentByClass<USpringArmComponent>();
	}
	
}

void UActionLockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsValid(TargetActor))
	{
		FVector  TargetLocation = TargetActor->GetActorLocation();
		FVector  CurrentLocation = OwnerRef->GetActorLocation();
		double Distance = FVector::Distance(CurrentLocation,TargetLocation);
		if (Distance >= BreakLockOnDistance)
		{
			StopLockOn();
			return;
		}
		TargetLocation.Z-=125;
		FRotator NewRotation=UKismetMathLibrary::FindLookAtRotation(CurrentLocation,TargetLocation);
		ControllerRef->SetControlRotation(NewRotation);
	}
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
		if (HitResult.GetActor()->Implements<UActionEnemy_Interface>())
		{
			ControllerRef->SetIgnoreLookInput(true);
			CharacterMovementRef->bOrientRotationToMovement=false;
			CharacterMovementRef->bUseControllerDesiredRotation=true;
			TargetActor=HitResult.GetActor();
			SpringArmRef->TargetOffset=FVector(0,0,100);
			IActionEnemy_Interface::Execute_OnSelected(TargetActor);
			OnUpdateTargetDelegate.Broadcast(TargetActor);
		}
	}
	
}

void UActionLockOnComponent::StopLockOn()
{
	IActionEnemy_Interface::Execute_OnDeselected(TargetActor);
	TargetActor=nullptr;
	CharacterMovementRef->bOrientRotationToMovement=true;
	CharacterMovementRef->bUseControllerDesiredRotation=false;
	SpringArmRef->TargetOffset=FVector::ZeroVector;
	ControllerRef->ResetIgnoreLookInput();
	OnUpdateTargetDelegate.Broadcast(TargetActor);
}

void UActionLockOnComponent::ToggleLockOn()
{
	if (IsValid(TargetActor))
	{
		StopLockOn();
	}
	else
	{
		StartLockOn();
	}
}
