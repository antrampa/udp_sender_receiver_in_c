#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    printf("Welcome to UDP Sender\n");
    if(argc != 4) {
        printf("Usage: %s <IP_ADDRESS> <PORT> <MESSAGE>\n", argv[0]);
        return 1;
    }

    printf("Target IP: %s\n", argv[1]);
    printf("Target Port: %s\n", argv[2]);

    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char *message = argv[3]; // ? argv[3] : "Hello Antonis UDP";

    // Initialize Winsock
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }

    // Create socket
    if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
        return 1;
    }

    //Server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]); // target IP from command line
    server.sin_port = htons(atoi(argv[2]));       // target port from command line
    
    // Send message
    if (sendto(sock, message, strlen(message), 0,
               (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) 
    {
        printf("sendto failed: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Message sent: %s\n", message);

    closesocket(sock);
    WSACleanup();
    return 0;
}   