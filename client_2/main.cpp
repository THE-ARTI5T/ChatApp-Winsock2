#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<thread>
#include<string>
using namespace std;


#pragma comment(lib,"ws2_32.lib")

/*
	Initialize winsock
	create socket
	connect to the server
	send/recv
	close the socket
*/

// Initialize the window socket library
bool Initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}


void sendMessage(SOCKET s){
	cout << "Enter your Chatname : " << endl;
	string name;
	getline(cin, name);
	string message;

	while (1) {
		getline(cin,message);
		string msg = name+" : "+message;
		int bytesent=send(s, msg.c_str(), msg.length(),0);
		if (bytesent == SOCKET_ERROR) {
			cout << "Error sending message." << endl;
			break;
		}
		if (message == "quit") {
			cout << "Stopping the chat." << endl;
			break;
		}
	}
	closesocket(s);
	WSACleanup();
}


void receiveMessage(SOCKET s) {
	// Recv
	char buffer[4096];
	
	string recvMsg = "";
	while (1) {
		int recvLength = recv(s, buffer, sizeof(buffer), 0);

		if (recvLength <= 0) {
			cout << "Disconnected from the server." << endl;
			break;
		}
		else {
			recvMsg = string(buffer, recvLength);
			cout << recvMsg << endl;
		}
	}
	closesocket(s);
	WSACleanup();
}


int main()
{
	if (!Initialize()) {
		cout << "Initialize winsock failed";
		return 1;
	}

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		cout << "INVALID Socket Created" << endl;
		return 1;
	}

	int port = 12345;
	string serveraddress = "127.0.0.1";
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);


	// Bind
	inet_pton(AF_INET, serveraddress.c_str(),&(serveraddr.sin_addr));


	// Connect
	if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "Not able to connect to server" << endl;
		cout << ": " << WSAGetLastError();
		closesocket(s);
		WSACleanup();
		return 1;
	}
	cout << "Successfully connected to server" << endl;

	thread senderThread(sendMessage, s);
	thread receiverThread(receiveMessage, s);

	senderThread.join();
	receiverThread.join();

	return 0;
}