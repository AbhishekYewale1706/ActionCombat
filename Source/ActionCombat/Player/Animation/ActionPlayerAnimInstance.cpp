#include "ActionPlayerAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UActionPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());
}

void UActionPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character)
	{
		Character = Cast<ACharacter>(TryGetPawnOwner());
	}

	if (!Character)
	{
		return;
	}

	Velocity = Character->GetVelocity();
	Velocity.Z = 0.0f;

	Speed = Velocity.Size();

	UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();

	bIsInAir = MoveComp->IsFalling();

	Acceleration = MoveComp->GetCurrentAcceleration();

	bIsAccelerating = !Acceleration.IsNearlyZero();

	if (!Velocity.IsNearlyZero())
	{
		const FVector Forward = Character->GetActorForwardVector();
		const FVector Right = Character->GetActorRightVector();

		const FVector NormalizedVelocity = Velocity.GetSafeNormal();

		const float ForwardDot = FVector::DotProduct(Forward, NormalizedVelocity);
		const float RightDot = FVector::DotProduct(Right, NormalizedVelocity);

		Direction = FMath::RadiansToDegrees(FMath::Atan2(RightDot, ForwardDot));
	}
	else
	{
		Direction = 0.f;
	}
}