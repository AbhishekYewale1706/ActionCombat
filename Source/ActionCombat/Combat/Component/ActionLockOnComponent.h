// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionLockOnComponent.generated.h"

class ACharacter;
class UCharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONCOMBAT_API UActionLockOnComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	 TObjectPtr<ACharacter>OwnerRef;
	 TObjectPtr<APlayerController> ControllerRef;
	 TObjectPtr<UCharacterMovementComponent> CharacterMovementRef;
	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius=750.f;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void StartLockOn();
	
	UActionLockOnComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
};
