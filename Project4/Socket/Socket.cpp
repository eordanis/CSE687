#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

#define BUFFERLENGTH 512
#define PORT "2323"
#define HOST "127.0.0.1"

// Creating SOCKET variables
SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;

// Variables to hold the responses
int resultResponse, sendResponse;

void SocketShutdown();

int main()
{
    struct addrinfo* result = NULL;
    struct addrinfo hints;

    WSADATA wsaData;

    // Creating a buffer for the message
    char recvbuf[BUFFERLENGTH] = { 0 };
    int recvbuflen = BUFFERLENGTH;

    // Initialize WINSOCK. Returns INT
    resultResponse = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (resultResponse == 0) {

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        resultResponse = getaddrinfo(HOST, PORT, &hints, &result);

        if (resultResponse == 0) {

            // Create a SOCKET for connecting to server
            ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

            if (ListenSocket == INVALID_SOCKET) {
                printf("Creating SOCKET error: %ld\n", WSAGetLastError());
                freeaddrinfo(result);
                WSACleanup();
                return 1;
            }

            // BIND SOCKET
            resultResponse = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
            if (resultResponse == SOCKET_ERROR) {
                printf("TCP SOCKET Error: %d\n", WSAGetLastError());
                freeaddrinfo(result);
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }

            freeaddrinfo(result);

            // Listen SOCKET
            resultResponse = listen(ListenSocket, SOMAXCONN);
            if (resultResponse == SOCKET_ERROR) {
                printf("LISTEN Error: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }

            // Accept Client SOCKET
            ClientSocket = accept(ListenSocket, NULL, NULL);
            if (ClientSocket == INVALID_SOCKET) {
                printf("ACCEPT error: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }

            // Listening
            do {
                resultResponse = recv(ClientSocket, recvbuf, recvbuflen, 0);

                // RECV Response
                if (resultResponse > 0) {
                    printf("Message received: %s\n", recvbuf);
                    const char* message;

                    std::string s(recvbuf);

                    if (s == "0001") {
                        std::string choice;
                        std::cout << "Type 'M' to start the Map Function: ";
                        std::cin >> choice;

                        if (choice == "M" || choice == "m") {

                            // Tell Client to Start Map
                            message = "Map";
                        }
                        else {
                            // Send the text from the server
                            message = choice.c_str();
                        }

                        sendResponse = send(ClientSocket, message, recvbuflen, 0);
                        if (sendResponse == SOCKET_ERROR) {
                            printf("SEND failed: %d\n", WSAGetLastError());
                            closesocket(ClientSocket);
                            WSACleanup();
                            return 1;
                        }
                    }
                    else if (s == "0002") {
                        std::string choice;
                        std::cout << "Type 'R' to start the Map Function: ";
                        std::cin >> choice;

                        if (choice == "R" || choice == "r") {

                            // Tell Client to Start Map
                            message = "Reduce";
                        }
                        else {

                            // Send the text from the server
                            message = choice.c_str();
                        }
                        
                        sendResponse = send(ClientSocket, message, recvbuflen, 0);
                        if (sendResponse == SOCKET_ERROR) {
                            printf("SEND failed: %d\n", WSAGetLastError());
                            closesocket(ClientSocket);
                            WSACleanup();
                            return 1;
                        }
                    }
                    else if (s == "exit") {

                        SocketShutdown();
                    }
                }
                else if (resultResponse == 0) {
                    printf("Closing SOCKET Connection\n");
                }
                else {
                    printf("RECV Failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }

            } while (resultResponse > 0);

        }
        else {
            printf("getaddrinfo Failed: %d\n", resultResponse);
            WSACleanup();
            return 1;
        }
    }
    else
    {
        printf("WSAStartup Failed: %d\n", resultResponse);
        return 1;
    }
}

void SocketShutdown() {

    // Closing Connection
    int resultResponse = shutdown(ClientSocket, SD_SEND);
    if (resultResponse == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
    }

    // Close the sockets
    closesocket(ClientSocket);
    WSACleanup();
}
