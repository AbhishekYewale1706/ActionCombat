// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ActionCombat/Interface/ActionPlayer_Interface.h"
#include "ActionPlayer.generated.h"


class UActionPlayerAnimInstance;
class UActionLockOnComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;


UCLASS()
class ACTIONCOMBAT_API AActionPlayer : public ACharacter , public IActionPlayer_Interface
{
	GENERATED_BODY()
	
	
private:
	

protected:
	
	// Camera
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

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

	//Component Ref
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UActionLockOnComponent>ActionLockOnComponentRef;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UActionPlayerAnimInstance> ActionPlayerAnimInstanceRef;
	
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LockCamera();
	
	UFUNCTION()
	void OnTargetUpdated(AActor* TargetActor);
	
	virtual void BeginPlay() override;
	
public:
	AActionPlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
