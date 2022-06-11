#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "./Header/MapReduceUtils.h"
#include "./Header/Client.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512

int Client::SendMessage(const char* message) 
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL, * ptr = NULL, hints;


    // Create an object to the Utils class
    MapReduceUtils utils;

    // Create the buffer that will send the message
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize WINSOCK
    int response = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (response != 0) {
        utils.logMessage("Client::SendMessage: WSAStartup has an error");
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    response = getaddrinfo("2323", "2323", &hints, &result);

    if (response != 0) {
        utils.logMessage("Client::SendMessage: Error getting address");
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        response = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (response == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    response = send(ConnectSocket, message, (int)strlen(message), 0);
    if (response == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", response);

    // shutdown the connection since no more data will be sent
    response = shutdown(ConnectSocket, SD_SEND);
    if (response == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {

        response = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (response > 0)
            printf("Bytes received: %d\n", response);
        else if (response == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (response > 0);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}