// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionLockOnComponent.generated.h"

class USpringArmComponent;
class ACharacter;
class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnUpdateTargetSignature,UActionLockOnComponent,OnUpdateTargetDelegate,AActor*,NewTargetActorRef);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONCOMBAT_API UActionLockOnComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	TObjectPtr<ACharacter>OwnerRef;
	TObjectPtr<APlayerController> ControllerRef;
	TObjectPtr<UCharacterMovementComponent> CharacterMovementRef;
	TObjectPtr<USpringArmComponent> SpringArmRef;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default Value")
	float Radius=750.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default Value")
	double BreakLockOnDistance=1000.f;
	
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnUpdateTargetSignature OnUpdateTargetDelegate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> TargetActor;
	
	UFUNCTION(BlueprintCallable)
	void StartLockOn();
	
	UFUNCTION(BlueprintCallable)
	void StopLockOn();
	
	UFUNCTION(BlueprintCallable)
	void ToggleLockOn();
	
	UActionLockOnComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
};
