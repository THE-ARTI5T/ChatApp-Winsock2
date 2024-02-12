# Multi-Client Chat Application

This is a simple multi-client chat application implemented in C++ using Winsock2 API for Windows platform. The project consists of a server application that can handle multiple client connections concurrently, and a client application that allows users to connect to the server and communicate with each other via text messages.

## Features

- **Server Application**:
  - Accepts multiple client connections simultaneously.
  - Facilitates real-time communication between connected clients.
  - Handles error conditions gracefully and ensures robustness.

- **Client Application**:
  - Connects to the server using TCP/IP socket communication.
  - Allows users to send and receive text messages in a chat-like interface.
  - Supports seamless termination of the chat session.

## Prerequisites

- Windows operating system (for both server and client applications).
- Visual Studio (or any other C++ compiler) for building the project.

## Usage

1. **Server Application**:
   - Compile and run the `main.cpp` file in server folder to start the server.
   - The server will listen for incoming connections on a specified port(i.e. 12345 in this case).

2. **Client Application**:
   - Compile and run the `main.cpp` file in the client folder to start the client.
   - Enter the server IP address and port number to connect to the server.
   - Start chatting with other connected clients.

## VIDEO DEMO
### Youtube Link : https://youtu.be/IJ8G7lp5dJk
### Drive Link : https://drive.google.com/file/d/1P08U5dREFQ6iodNvWY8q7vrS0TDdlrWm/view?usp=sharing

## Screenshot
![ChatApp-Winsock](https://github.com/THE-ARTI5T/ChatApp-Winsock2/assets/103200040/3e8d6cd4-71ec-4695-a424-4bd448d0678d)

