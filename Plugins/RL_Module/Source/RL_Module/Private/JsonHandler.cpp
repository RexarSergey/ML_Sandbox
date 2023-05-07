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

FGymCommandStruct JsonHandler::ReadFGymCommandStruct(FString JsonString, bool& bSuccess)
{
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonString, bSuccess);
	if (!bSuccess) {
		return FGymCommandStruct();
	}
	FGymCommandStruct Out;
	if (!FJsonObjectConverter::JsonObjectToUStruct<FGymCommandStruct>(JsonObject.ToSharedRef(), &Out)) {
		bSuccess = false;
		return FGymCommandStruct();
	}
	bSuccess = true;

	return Out;
}

FString JsonHandler::CreateFGymCommandStruct(FGymCommandStruct StepStruct, bool& bSuccess)
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
