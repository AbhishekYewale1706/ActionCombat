
#include "ActionPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "ActionCombat/Combat/Component/ActionLockOnComponent.h"
#include "Animation/ActionPlayerAnimInstance.h"

AActionPlayer::AActionPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,540.f,0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;

	CameraBoom =CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;

	FollowCamera =CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("Weapon_Socket"));
	
	// Component Ref
	ActionLockOnComponentRef=CreateDefaultSubobject<UActionLockOnComponent>("ActionLockOnComponent");
	
}

void AActionPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	ActionPlayerAnimInstanceRef=Cast<UActionPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
	if (ActionLockOnComponentRef)
	{
		ActionLockOnComponentRef->OnUpdateTargetDelegate.AddDynamic(this,&AActionPlayer::OnTargetUpdated);
	}
	
	if(APlayerController* PC =Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}
	
}

void AActionPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input =Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AActionPlayer::Move);
	Input->BindAction(LookAction,ETriggerEvent::Triggered,this,&AActionPlayer::Look);
	Input->BindAction(JumpAction,ETriggerEvent::Started,this,&ACharacter::Jump);
	Input->BindAction(JumpAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
	Input->BindAction(LockCameraAction,ETriggerEvent::Started,this,&AActionPlayer::LockCamera);
}

void AActionPlayer::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();
	if(Controller)
	{
		FRotator Rotation =Controller->GetControlRotation();
		FRotator YawRotation(0,Rotation.Yaw,0);
		FVector Forward =FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector Right =FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward,Movement.Y);
		AddMovementInput(Right,Movement.X);
	}
}

void AActionPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxis =Value.Get<FVector2D>();
	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

void AActionPlayer::LockCamera()
{
	ActionLockOnComponentRef->ToggleLockOn();
}

void AActionPlayer::OnTargetUpdated(AActor* TargetActor)
{
	if (ActionPlayerAnimInstanceRef)
	{
		ActionPlayerAnimInstanceRef->bIsCombat = IsValid(TargetActor);
	}
}
