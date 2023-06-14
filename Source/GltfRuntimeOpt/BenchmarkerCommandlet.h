// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "UObject/Object.h"
#include "BenchmarkerCommandlet.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GLTFBenchmarker, Log, All)

/**
 * 
 */
UCLASS()
class GLTFRUNTIMEOPT_API UBenchmarkerCommandlet : public UCommandlet
{
	GENERATED_BODY()
public:
	virtual int32 Main(const FString& Params) override;
};
