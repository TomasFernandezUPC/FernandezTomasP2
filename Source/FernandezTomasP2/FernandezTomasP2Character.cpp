// Copyright Epic Games, Inc. All Rights Reserved.

// Los include incluyen el archivo necesario correspondiente que se necesitan
#include "FernandezTomasP2Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "FernandezTomasP2.h"

// Constructor de la clase del personaje
AFernandezTomasP2Character::AFernandezTomasP2Character()
{
	// Inicializa el tamaño de la cápsula de colisión (ancho = 42, alto = 96)
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Evita que el personaje rote con el pitch del controlador (mirar arriba/abajo)
	bUseControllerRotationPitch = false;
	// Evita que el personaje rote con el yaw del controlador (giro izquierda/derecha)
	bUseControllerRotationYaw = false;
	// Evita que el personaje rote con el roll del controlador (inclinación lateral)
	bUseControllerRotationRoll = false;

	// Activa que el personaje rote automáticamente hacia la dirección en la que se mueve
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Define la velocidad de rotación (500 grados/seg en yaw)
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Configura la fuerza con la que el personaje salta en el eje Z 
	// Para variar le cambie la velocidad de salto  de 500 a 800
	GetCharacterMovement()->JumpZVelocity = 800.f;
	// Configura cuánto control tiene el jugador en el aire
	GetCharacterMovement()->AirControl = 0.35f;
	// Establece la velocidad máxima de caminar
	// Para variar le cambie la  maxima velocidad de 500 a 1200
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;
	// Establece la velocidad mínima al moverse con control analógico
	// Para variar le cambie la  velocidad de 20 a 50
	GetCharacterMovement()->MinAnalogWalkSpeed = 50.f;
	// Configura la tasa de frenado al detenerse en el suelo
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	// Configura la tasa de frenado al caer en el aire
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Crea un CameraBoom (brazo que mantiene la cámara a cierta distancia del personaje)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// Lo adjunta al componente raíz del personaje
	CameraBoom->SetupAttachment(RootComponent);
	// Establece la longitud del brazo de la cámara (400 unidades)
	CameraBoom->TargetArmLength = 400.0f;
	// Hace que el CameraBoom rote según el controlador del jugador
	CameraBoom->bUsePawnControlRotation = true;

	// Crea la cámara que seguirá al personaje
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// La adjunta al extremo del CameraBoom (socket predeterminado)
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Desactiva que la cámara rote con el controlador (la rotación depende del CameraBoom)
	FollowCamera->bUsePawnControlRotation = false;

	// NOTA: El Mesh y la animación del personaje se asignan desde el Blueprint derivado
}


// Configura las entradas del jugador
void AFernandezTomasP2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Verifica si el componente de entrada es del tipo mejorado (Enhanced Input)
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Asigna acción de salto cuando empieza a presionarse
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		// Asigna acción de detener salto cuando se suelta
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Asigna acción de movimiento cuando se detecta entrada
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFernandezTomasP2Character::Move);
		// Asigna acción de mirar con el mouse cuando se detecta entrada
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AFernandezTomasP2Character::Look);

		// Asigna acción de mirar con joystick/otro control
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFernandezTomasP2Character::Look);

		// Muestra un mensaje en pantalla cuando se presiona la tecla asignada a TextAction
		EnhancedInputComponent->BindAction(TextAction, ETriggerEvent::Started, this, &AFernandezTomasP2Character::Texto);
	
		// Muestra un mensaje en pantalla cuando se presiona la tecla asignada a CurarVida
		EnhancedInputComponent->BindAction(HealAction, ETriggerEvent::Started, this, &AFernandezTomasP2Character::CurarVida);

		// Muestra un mensaje en pantalla cuando se presiona la tecla asignada a MostrarVida
		EnhancedInputComponent->BindAction(LifeAction, ETriggerEvent::Started, this, &AFernandezTomasP2Character::MostrarVida);
	}
	else
	{
		// Si no se encuentra un Enhanced Input Component, muestra un error en el log
		UE_LOG(LogFernandezTomasP2, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


// Maneja la acción de moverse
void AFernandezTomasP2Character::Move(const FInputActionValue& Value)
{
	// Convierte la entrada en un vector 2D (X = lateral, Y = adelante/atrás)
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Envía los valores a la función DoMove
	DoMove(MovementVector.X, MovementVector.Y);
}


// Maneja la acción de mirar
void AFernandezTomasP2Character::Look(const FInputActionValue& Value)
{
	// Convierte la entrada en un vector 2D (X = yaw, Y = pitch)
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Envía los valores a la función DoLook
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}


// Función que traduce los valores de movimiento en movimiento real del personaje
void AFernandezTomasP2Character::DoMove(float Right, float Forward)
{
	// Verifica que exista un controlador
	if (GetController() != nullptr)
	{
		// Obtiene la rotación del controlador
		const FRotator Rotation = GetController()->GetControlRotation();
		// Se queda solo con el valor de yaw (horizontal)
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Obtiene el vector que apunta hacia adelante
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Obtiene el vector que apunta hacia la derecha
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Aplica movimiento hacia adelante
		AddMovementInput(ForwardDirection, Forward);
		// Aplica movimiento hacia la derecha
		AddMovementInput(RightDirection, Right);
	}
}


// Función que traduce los valores de entrada en rotación de cámara/controlador
void AFernandezTomasP2Character::DoLook(float Yaw, float Pitch)
{
	// Verifica que exista un controlador
	if (GetController() != nullptr)
	{
		// Aplica rotación horizontal (yaw)
		AddControllerYawInput(Yaw);
		// Aplica rotación vertical (pitch)
		AddControllerPitchInput(Pitch);
	}
}


// Inicia un salto
void AFernandezTomasP2Character::DoJumpStart()
{
	// Llama a la función de salto del personaje
	Jump();
}


// Finaliza un salto
void AFernandezTomasP2Character::DoJumpEnd()
{
	// Llama a la función que detiene el salto
	StopJumping();
}

void AFernandezTomasP2Character::Texto()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Has presionado la tecla T"));
}

void AFernandezTomasP2Character::CurarVida()
{
	Vida += 20;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Te has curado 20 de vida"));
	if (Vida > 100)
	{
		Vida = 100;
	}
	MostrarVida();
}
void AFernandezTomasP2Character::MostrarVida()
{
	FString VidaTexto = FString::Printf(TEXT("Vida: %d"), Vida);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, VidaTexto);
}