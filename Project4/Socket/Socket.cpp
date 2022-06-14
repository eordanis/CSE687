#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

#define BUFFERLENGTH 512
#define PORT "2323"

// Creating SOCKET variables
SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;

// Variables to hold the responses
int resultResponse, sendResponse;

int main()
{
    struct addrinfo* result = NULL;
    struct addrinfo hints;

    WSADATA wsaData;

    // Creating a buffer for the message
    char recvbuf[BUFFERLENGTH];
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
        resultResponse = getaddrinfo("127.0.0.1", PORT, &hints, &result);

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
                printf("accept failed with error: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }

            // Continue to listen
            do {
                resultResponse = recv(ClientSocket, recvbuf, recvbuflen, 0);
                if (resultResponse > 0) {
                    printf("Bytes received: %d\n", resultResponse);

                    // Echo the buffer back to the sender
                    sendResponse = send(ClientSocket, recvbuf, resultResponse, 0);
                    if (sendResponse == SOCKET_ERROR) {
                        printf("send failed with error: %d\n", WSAGetLastError());
                        closesocket(ClientSocket);
                        WSACleanup();
                        return 1;
                    }
                    printf("Bytes sent: %d\n", sendResponse);
                }
                else if (resultResponse == 0)
                    printf("Connection closing...\n");
                else {
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }

            } while (resultResponse > 0);

        }
        else {
            printf("getaddrinfo failed with error: %d\n", resultResponse);
            WSACleanup();
            return 1;
        }
    }
    else
    {
        printf("WSAStartup failed with error: %d\n", resultResponse);
        return 1;
    }
}

void SocketShutdown() {
    // shutdown the connection since we're done
    int resultResponse = shutdown(ClientSocket, SD_SEND);
    if (resultResponse == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
}
