// Fill out your copyright notice in the Description page of Project Settings.


#include "BenchmarkerCommandlet.h"

#include "glTFRuntimeParser.h"

DEFINE_LOG_CATEGORY(GLTFBenchmarker)

#define LOG(x,...) UE_LOG(GLTFBenchmarker, Log, TEXT(x), __VA_ARGS__)

int32 UBenchmarkerCommandlet::Main(const FString& Params)
{
	LOG("Hello");
	FGenericPlatformProcess::ConditionalSleep([this](){return true;}, 5.0f);
	FglTFRuntimeParser parser;
	return 0;
}
