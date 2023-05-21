// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonHandler.h"
//#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

JsonHandler::JsonHandler()
{
}

JsonHandler::~JsonHandler()
{
}

TSharedPtr<FJsonObject> JsonHandler::ReadJson(FString JsonString, bool& bSuccess)
{
	TSharedPtr<FJsonObject> Out;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), Out)) {
		UE_LOG(LogTemp, Warning, TEXT("Read Json Failed: %s"), *JsonString);
		bSuccess = false;
		return nullptr;
	}
	bSuccess = true;
	return Out;
}

FString JsonHandler::CreateJson(TSharedPtr<FJsonObject> JsonObject, bool& bSuccess)
{
	FString Out;
	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&Out, 0))) {
		UE_LOG(LogTemp, Warning, TEXT("Write Json Failed"));
		bSuccess = false;
		return FString();
	}
	bSuccess = true;
	return Out;
}

FPythonCommandStruct JsonHandler::ReadFGymCommandStruct(FString JsonString, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonString, bSuccess);
	if (!bSuccess) {
		return FPythonCommandStruct();
	}
	FPythonCommandStruct Out;
	if (!FJsonObjectConverter::JsonObjectToUStruct<FPythonCommandStruct>(JsonObject.ToSharedRef(), &Out)) {
		bSuccess = false;
		return FPythonCommandStruct();
	}
	bSuccess = true;

	return Out;
}

FString JsonHandler::CreateFPythonCommandStruct(FPythonCommandStruct StepStruct, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(StepStruct);
	if (JsonObject == nullptr) {
		bSuccess = false;
		return FString();
	}

	return CreateJson(JsonObject, bSuccess);
}

FGymStateStruct JsonHandler::ReadFGymStateStruct(FString JsonString, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonString, bSuccess);
	if (!bSuccess) {
		return FGymStateStruct();
	}
	FGymStateStruct Out;
	if (!FJsonObjectConverter::JsonObjectToUStruct<FGymStateStruct>(JsonObject.ToSharedRef(), &Out)) {
		bSuccess = false;
		return FGymStateStruct();
	}
	bSuccess = true;

	return Out;
}

FString JsonHandler::CreateFGymStateStruct(FGymStateStruct StepStruct, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(StepStruct);
	if (JsonObject == nullptr) {
		bSuccess = false;
		return FString();
	}

	return CreateJson(JsonObject, bSuccess);
}

FDQNLearningStruct JsonHandler::ReadFDQNLearningStruct(FString JsonString, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonString, bSuccess);
	if (!bSuccess) {
		return FDQNLearningStruct();
	}
	FDQNLearningStruct Out;
	if (!FJsonObjectConverter::JsonObjectToUStruct<FDQNLearningStruct>(JsonObject.ToSharedRef(), &Out)) {
		bSuccess = false;
		return FDQNLearningStruct();
	}
	bSuccess = true;

	return Out;
}

FString JsonHandler::CreateFDQNLearningStruct(FDQNLearningStruct StepStruct, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(StepStruct);
	if (JsonObject == nullptr) {
		bSuccess = false;
		return FString();
	}

	return CreateJson(JsonObject, bSuccess);
}
