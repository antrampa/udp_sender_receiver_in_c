#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) 
{
    printf("Welcome to UDP Receiver\n");
    if (argc != 2) {
        printf("Usage: %s <PORT>\n", argv[0]);
        return 1;
    }
    
    int port = atoi(argv[1]);
    printf("UDP Receiver listening on port %d\n", port);

    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);
    char buffer[2048];

    // Start Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        return 1;
    }

    // Bind to the given port
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    server.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Waiting for UDP messages...\n");

    // Receive loop
    while (1) {
        int recv_len = recvfrom(
            sock,
            buffer,
            sizeof(buffer) - 1,
            0,
            (struct sockaddr *)&client,
            &client_len
        );

        if (recv_len == SOCKET_ERROR) {
            printf("recvfrom failed: %d\n", WSAGetLastError());
            break;
        }

        buffer[recv_len] = '\0'; // null-terminate message

        printf("\nReceived message from %s:%d\n",
               inet_ntoa(client.sin_addr),
               ntohs(client.sin_port));

        printf("Message: %s\n", buffer);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}