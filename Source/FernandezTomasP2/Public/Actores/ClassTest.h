// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassTest.generated.h"

UCLASS()
class FERNANDEZTOMASP2_API AClassTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClassTest();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
