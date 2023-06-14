// Fill out your copyright notice in the Description page of Project Settings.


#include "BenchmarkerCommandlet.h"

#include "BenchmarkerBlueprintFunctions.h"
#include "Editor.h"
#include "glTFRuntimeAssetActor.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "GltfRuntimeOptGameModeBase.h"
#include "glTFRuntimeParser.h"
#include "LevelEditorSubsystem.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/DeferredMessageLog.h"

DEFINE_LOG_CATEGORY(GLTFBenchmarker)

#define LOG(x,...) UE_LOG(GLTFBenchmarker, Warning, TEXT(x), __VA_ARGS__)

int32 UBenchmarkerCommandlet::Main(const FString& Params)
{
	FString LevelAssetPath = TEXT("/Game/TestWorld");
	if(!GEditor->GetEditorSubsystem<ULevelEditorSubsystem>()->LoadLevel(LevelAssetPath))
	{
		LOG("Failed to load world");
		return -1;
	}
	
	UWorld* World = UWorld::CreateWorld(EWorldType::Game, true);
	FWorldContext& WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);
	WorldContext.SetCurrentWorld(World);

	UGameInstance* GameInstance = NewObject<UGameInstance>(GEngine);
	FURL URL;
	World->GetWorldSettings(false, false)->DefaultGameMode = AGltfRuntimeOptGameModeBase::StaticClass();
	World->SetGameInstance(GameInstance);
	World->SetGameMode(URL);
	World->InitializeActorsForPlay(URL);
	World->BeginPlay();
	
	FTransform Transform;
	FglTFRuntimeConfig Config;
	TArray<FString> GltfFiles = UBenchmarkerBlueprintFunctions::GetGltfFiles();
	for(const auto& File : GltfFiles)
	{
		FString FilePath = UBenchmarkerBlueprintFunctions::GetGltfFilePath(File);
		AglTFRuntimeAssetActor* GltfActor = World->SpawnActorDeferred<AglTFRuntimeAssetActor>(AglTFRuntimeAssetActor::StaticClass(), Transform);
		UglTFRuntimeAsset* Asset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(FilePath, false, Config);
		GltfActor->Asset = Asset;
		UGameplayStatics::FinishSpawningActor(GltfActor, Transform);
	}

	GEngine->DestroyWorldContext(World);
	World->DestroyWorld(true);
	
	FDeferredMessageLog::Flush();
	return 0;
}
