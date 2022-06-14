///////////////////////////////////////////////////////////////////
//  Client.cpp   -  class file for Client class                  //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 4                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////
#pragma once
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
#include "./Header/FileManagement.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define BUFFERLENGTH 512
#define PORT "2323"
#define HOST "127.0.0.1"

Client::Client(FileManagement fm) {
    _fm = fm;
}

int Client::SendNewMessage(const char* message)
{
    struct addrinfo* result = NULL, * ptr = NULL, hints;

    // Create an object to the Utils class
    MapReduceUtils utils;

    // Create the buffer that will send the message
    char recvbuf[BUFFERLENGTH] = { 0 };
    int recvbuflen = BUFFERLENGTH;

    // Initialize WINSOCK
    int response = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (response != 0) {
        utils.logMessage("Client::SendMessage: WSAStartup has an error");
        return 1;
    }

    // Clearing the memory
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    // Using the LocalHost and static port number
    response = getaddrinfo(HOST, PORT, &hints, &result);

    // Logging error if necesssary
    if (response != 0) {
        WSACleanup();
        utils.throwException("Client::SendMessage ", "Error getting address");
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        // Logging error if necessary
        if (ConnectSocket == INVALID_SOCKET) {
            WSACleanup();
            utils.throwException("Client::SendMessage: Socket Creation Error", "" + WSAGetLastError());
            return 1;
        }

        // Connect to the SOCKET Server
        response = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

        // Logging error if necessary
        if (response == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    // Send the message to the SOCKET Server
    response = send(ConnectSocket, message, (int)strlen(message), 0);
    if (response == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        WSACleanup();
        utils.throwException("Client::SendMessage: Socket Send Error", "" + WSAGetLastError());
        return 1;
    }

    // Receive until the peer closes the connection
    do {
        response = recv(ConnectSocket, recvbuf, recvbuflen, 0);

        if (response > 0) {
            std::string s(recvbuf);
            utils.logMessage("Message received: " + s + "\n");
            if (s == "Map") {
                mapRan = true;
                StartMap();

                message = "0002";
                int sendResponse = send(ConnectSocket, message, (int)strlen(message), 0);
                if (sendResponse == SOCKET_ERROR) {
                    closesocket(ConnectSocket);
                    WSACleanup();
                    utils.throwException("Client::SendMessage: Socket Send Error", "" + WSAGetLastError());
                    return 1;
                }
            }
            else if (s == "Reduce") {
                reduceRan = true;
                StartReduce();
                ShutDownServer();
            }
            else {
                std::string response;

                if (!mapRan) {
                    message = "0001";
                }
                else if (!reduceRan) {
                    message = "0002";
                }

                int sendResponse = send(ConnectSocket, message, (int)strlen(message), 0);
                if (sendResponse == SOCKET_ERROR) {
                    closesocket(ConnectSocket);
                    WSACleanup();
                    utils.throwException("Client::SendMessage: Socket Send FAILED", "" + WSAGetLastError());
                    return 1;
                }
            }
        }
        else if (response == 0) {
            utils.logMessage("Closing Connection with Client\n");
        }
        else {
            closesocket(ConnectSocket);
            WSACleanup();
            utils.throwException("Client::SendMessage: Socket RECV FAILED", "" + WSAGetLastError());
            return 1;
        }

    } while (response > 0);

    return 0;
}

void Client::ShutDownServer() {

    // When the program is complete, close the connection
    int response = shutdown(ConnectSocket, SD_SEND);
    closesocket(ConnectSocket);
    WSACleanup();
    if (response == SOCKET_ERROR) {
        MapReduceUtils utils;
        utils.throwException("Client::SendMessage: Shutdown failed with error", "" + WSAGetLastError());
    }
}

void Client::Workflow() {

    /*
    * Partition valid input files into buckets per thread
    */
    _fm.partitionInput();

    /*
    * Start the Communication with the server
    */
    int response = SendNewMessage("0001");
}

void Client::StartMap() {

    /*
    * stub process(thread) that runs mapper and when complete, broadcasts socket message indicating completion
    */
    _fm.executeFileMapping();
}

void Client::StartReduce() {

    /*
    * stub process(thread) that listens for broadcast indicating mapper has successfully completed, then runs reducer
    */
    _fm.executeReduce();
}