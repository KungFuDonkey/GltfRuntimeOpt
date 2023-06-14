#include "BenchmarkerBlueprintFunctions.h"

#include "HAL/FileManagerGeneric.h"

class FFillArrayDirectoryVisitor : public IPlatformFile::FDirectoryVisitor
{
public:
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
	{
		if (bIsDirectory)
		{
			Directories.Add(FilenameOrDirectory);
		}
		else
		{
			Files.Add(FilenameOrDirectory);
		}
		return true;
	}

	TArray<FString> Directories;
	TArray<FString> Files;
};


FString UBenchmarkerBlueprintFunctions::GetGltfDir()
{
	return FPaths::Combine(FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), "Gltfs");
}

FString UBenchmarkerBlueprintFunctions::GetGltfFilePath(const FString& FileName)
{
	FString GltfsFolder = GetGltfDir();
	FString AssetFolder = FPaths::Combine(GltfsFolder, FileName);
	FString AssetPath = FPaths::Combine(AssetFolder, FileName + ".gltf");
	return AssetPath;
}

TArray<FString> UBenchmarkerBlueprintFunctions::GetGltfFiles()
{
	FString GltfsFolder = GetGltfDir();
	TArray<FString> Results;

	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FFillArrayDirectoryVisitor DirectoryVisitor;

	PlatformFile.IterateDirectory(*GltfsFolder, DirectoryVisitor);

	for(const auto& Folder : DirectoryVisitor.Directories)
	{
		Results.Add(FPaths::GetCleanFilename(Folder));
	}
	return Results;
}
