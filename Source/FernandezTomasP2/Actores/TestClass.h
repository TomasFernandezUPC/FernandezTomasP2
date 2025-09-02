// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestClass.generated.h"

UCLASS()
class FERNANDEZTOMASP2_API ATestClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestClass();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas")
	int Vida;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas")
	int Defensa;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas")
	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas")
	int Velocidad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas")
	int Inteligencia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas", meta = (ClampMin = "0.0", ClampMax = "70.0", UIMin = "0.0", UIMax = "100.0", ToolTip = "Es la Estamina que posee el personaje"))
	int Estamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estadisticas", meta = (ClampMin = "0.0", ClampMax = "70.0", UIMin = "0.0", UIMax = "350.0", ToolTip = "Es la Estamina que posee el personaje"))
	int Experiencia;





};
