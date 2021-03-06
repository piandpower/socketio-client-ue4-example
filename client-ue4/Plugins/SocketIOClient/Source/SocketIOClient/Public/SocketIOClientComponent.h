#pragma once

#include "sio_client.h"
#include "SocketIOClientComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIOCConnectedEventSignature);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIOCDisconnectedEventSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSIOCOnEventSignature, FString, Name, FString, Action);

UCLASS(ClassGroup = "Networking", meta = (BlueprintSpawnableComponent))
class SOCKETIOCLIENT_API USocketIOClientComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	/**
	* On all subscribed events
	*
	* @param Name of event
	* @param Data of event
	*/
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
		FSIOCOnEventSignature On;

	/**
	* Connect to a socket.io server
	*
	* @param AddressAndPort	the address in URL format with port
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Client Functions")
		void Connect(FString AddressAndPort);

	/**
	* Emit a string event with a string action
	*
	* @param Name	Event name
	* @param Data	string of received data
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Client Functions")
		void Emit(FString Name, FString Data);

	/**
	* Bind given event to our multicast delegate
	*
	* @param Name	Event name
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Client Functions")
		void Bind(FString Name);

protected:
	void HandleOnEvent(FString Name, FString Action);
	sio::client PrivateClient;
};