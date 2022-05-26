// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ExFactoryTextureGenerate.generated.h"

/**
 * 
 */
UCLASS()
class GEOTECH_SIXTHLESSON_API UExFactoryTextureGenerate : public UFactory
{
	GENERATED_BODY()
	
	UExFactoryTextureGenerate();
public:

	UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;

};
