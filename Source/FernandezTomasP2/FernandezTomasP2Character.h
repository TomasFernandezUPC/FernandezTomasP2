// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "FernandezTomasP2Character.generated.h"

// Declaración anticipada de la clase USpringArmComponent (brazo de cámara).
// Se declara aquí para poder usar punteros sin necesidad de incluir el header completo.
class USpringArmComponent;

// Declaración anticipada de la clase UCameraComponent (cámara del personaje).
class UCameraComponent;

// Declaración anticipada de la clase UInputAction (acción de entrada del sistema Enhanced Input).
class UInputAction;

// Declaración anticipada de la estructura FInputActionValue (almacena valores de entrada, ej. Vector2D).
struct FInputActionValue;


// Declara una categoría de log específica para este personaje.
// Esto permite registrar mensajes de depuración en el Output Log de Unreal.
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


/**
 * Clase de personaje controlable en tercera persona.
 * Implementa una cámara orbitante (que sigue y rota alrededor del personaje).
 */
UCLASS(abstract) // "abstract" indica que la clase no debe instanciarse directamente, sino heredarse.
class AFernandezTomasP2Character : public ACharacter // Hereda de ACharacter (personaje básico de UE).
{
	GENERATED_BODY() // Macro necesaria para la reflexión y el sistema de objetos de Unreal Engine.


		/** Brazo de cámara que posiciona la cámara detrás del personaje. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Cámara que sigue al personaje. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas")
	int Vida;

	/** Acción de entrada para saltar. */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	/** Acción de entrada para moverse. */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	/** Acción de entrada para mirar (ej. joystick derecho). */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	/** Acción de entrada para mirar con el mouse. */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	// Input de prueba para mostrar texto en la pantalla
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TextAction;

	// Input de prueba para curar vida en la pantalla
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* HealAction;

	// Input de prueba para mostrar vida en la pantalla
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LifeAction;

public:

	/** Constructor del personaje. */
	AFernandezTomasP2Character();

protected:

	/** Inicializa las vinculaciones de entrada (input bindings). */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Función llamada al recibir entrada de movimiento. */
	void Move(const FInputActionValue& Value);

	/** Función llamada al recibir entrada de mirada. */
	void Look(const FInputActionValue& Value);

public:

	/** Maneja el movimiento (accesible desde controles o interfaces en UI/Blueprints). */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	/** Maneja la mirada (accesible desde controles o interfaces en UI/Blueprints). */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Maneja el inicio del salto (accesible desde controles o interfaces). */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	/** Maneja el final del salto (accesible desde controles o interfaces). */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();
	/** Testeando */
	UFUNCTION(Blueprintcallable, Category = "Input")
	virtual void Texto();
	/** Creando la funcion de curar vida */
	UFUNCTION(Blueprintcallable, Category = "Input")
	virtual void CurarVida();
	UFUNCTION(Blueprintcallable, Category = "Input")
	/** Creando la funcion de mostrar vida */
	virtual void MostrarVida();

public:

	/** Devuelve el subobjeto CameraBoom (para acceso en código o Blueprints). */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Devuelve el subobjeto FollowCamera (para acceso en código o Blueprints). */
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};