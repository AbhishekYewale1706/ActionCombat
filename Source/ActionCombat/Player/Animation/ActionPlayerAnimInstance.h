// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ActionPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UActionPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	bool bIsCombat = false;
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float Direction = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	bool bIsInAir = false;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	bool bIsAccelerating = false;
	
	
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector Acceleration;

private:
	
	class ACharacter* Character;
};
