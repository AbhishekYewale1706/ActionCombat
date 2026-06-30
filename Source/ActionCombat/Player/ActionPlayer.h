// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ActionPlayer.generated.h"


class UActionLockOnComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;


UCLASS()
class ACTIONCOMBAT_API AActionPlayer : public ACharacter
{
	GENERATED_BODY()
	
	
private:
	

protected:
	
	// Camera
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;

	// Enhanced Input
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LockCameraAction;

	//Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UActionLockOnComponent>ActionLockOnComponent;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LockCamera();
	
	
	virtual void BeginPlay() override;
	
public:
	AActionPlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
