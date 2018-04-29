#pragma once

#include "utils/ServerClient.hpp"

#include <functional>
#include <string>
#include <thread>
#include <vector>

class SocketServer {
	public:
	// ========================== CONSTRUCTORS ========================= //
	SocketServer(std::string server_name, unsigned short server_port, unsigned int max_clients, std::function<void(SocketServer&, ServerClient&, std::string)> message_received_cb);

	// =========================== PROPERTIES ========================== //
	std::string serverName();
	unsigned short port();
	unsigned int maxClients();
	bool isUnixSock();

	bool isListening();
	bool isConfigured();

	// ======================== PUBLIC METHODS ========================= //
	bool startListening();
	bool stopListening();

	bool setUnixSock(bool unix_sock, std::string& error_msg);
	bool setConnectedCB(std::function<void(SocketServer&, ServerClient&)> connected_cb);
	bool setDisconnectedCB(std::function<void(SocketServer&, ServerClient&, std::string)> disconnected_cb);

	private:
	// ====================== PRIVATE VARIABLES ======================== //

	// Server configuration variables
	std::string server_name = "SocketServer";
	const unsigned short port;
	const unsigned int max_clients;
	bool is_unix_sock = false;

	// Server status variables
	bool is_listening = false;
	bool is_configured = false;

	// Listen thread variables
	std::thread listen_thread;

	// Callback function option variables
	bool use_connected_cb = false;
	bool use_disconnected_cb = false;
	bool use_default_cbs = true;

	// Callback function variables
	std::function<void(SocketServer&, ServerClient&, std::string message)> message_received_cb;
	std::function<void(SocketServer&, ServerClient&)> connected_cb;
	std::function<void(SocketServer&, ServerClient&, std::string)> disconnected_cb;
};