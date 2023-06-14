

#pragma once

#include "CoreMinimal.h"

#include "BenchmarkerBlueprintFunctions.generated.h"

/**
 * 
 */
UCLASS()
class GLTFRUNTIMEOPT_API UBenchmarkerBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	static FString GetGltfDir();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Gltf File Path", AutoCreateRefTerm = "LoaderConfig, Headers"), Category = "BenchmarkerUtils")
	static FString GetGltfFilePath(const FString& FileName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get GltfFiles", AutoCreateRefTerm = "LoaderConfig, Headers"), Category = "BenchmarkerUtils")
	static TArray<FString> GetGltfFiles();
};
