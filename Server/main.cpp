#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<thread>
#include<vector>
using namespace std;

#pragma comment (lib,"ws2_32.lib")

/* Steps For Server:
	Initialize winsock library
	create the socket
	get ip and port
	bind the ip/port with the socket
	listen on the socket
	accept
	recv and send
	close the socket
	cleanup the winsock
*/

// Initialize the window socket library
bool Initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}


void InteractWithClient(SOCKET clientSocket, vector<SOCKET> &clients) {
	// Send/recv

	cout << "Client Connected" << endl;

	// Recv
	char buffer[4096];
	while (1) {
		int byteRecv = recv(clientSocket, buffer, sizeof(buffer), 0);


		if (byteRecv <= 0) {
			cout << "Client Disconnected" << endl;
			break;
		}

		string message(buffer, byteRecv);
		cout << "Message from client :" << message << endl;

		for (auto client : clients) {
			if (client != clientSocket) {
				send(client, message.c_str(), message.length(), 0);
			}
		}
	}
	
	auto it = find(clients.begin(), clients.end(),clientSocket);
	if (it != clients.end()){
		clients.erase(it);
	}

	closesocket(clientSocket);
}


int main()
{
	if (!Initialize()) {
		cout << "Winsock Initialize Failed." << endl;
		return 1;
	}
	cout << "Server Pro" << endl;

	/* Socket Creation
		int sockfd = socket(domain, type, protocol)
	*/
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSocket == INVALID_SOCKET) {
		cout << "Socket creation failed" << endl;
		return 1;
	}

	// Create address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	// Convert ip adress to binary format
	// Convert the ip address(0.0.0.0) put it inside the sin_family in binary format
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "Address Structure Failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// Bind the ip and port with socket
	if (bind(listenSocket, reinterpret_cast<sockaddr*> (&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR){
		cout << "Bind Failed"<<endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// Listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "Listen Failed"<<endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	cout << "Server has started and listening on port : "<<port<<endl;

	vector<SOCKET> clients;

	while (1) {
		// Accept
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET) {
			cout << "Invalid Client Socket" << endl;
		}
		clients.push_back(clientSocket);
		thread t1(InteractWithClient, clientSocket,std::ref(clients));
		t1.detach();
	}

	
	closesocket(listenSocket);

	WSACleanup();
	return 0;
}