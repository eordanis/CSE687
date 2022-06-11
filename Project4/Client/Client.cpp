#include "stdafx.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>

#ifdef _WIN32
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501
#endif
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
#endif

#define PORT 2323

int main()
{
    int sock = 0;
    int valread = 0;
    int client_fd = 0;

    struct sockaddr_in serv_addr;

    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((client_fd
        = connect(sock, (struct sockaddr*)&serv_addr,
            sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    // closing the connected socket
    close(client_fd);
    return 0;
}