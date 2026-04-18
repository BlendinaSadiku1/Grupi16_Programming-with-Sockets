#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define PORT 4444
#define BUFFER_SIZE 2048

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Gabim ne socket!\n";
        return 1;
    }

    struct sockaddr_in serverAddr;
    int len = sizeof(serverAddr);

    std::string serverIP;
    std::cout << "Shkruaj IP e serverit (ose 127.0.0.1): ";
    std::getline(std::cin, serverIP);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());

//Loop qe klienti te mund te dergoj shume komanda
while (true) {
    std::string message;
    std::cout << "\nKomandat: read|file.txt OSE write|file.txt|teksti (ose 'exit'):\n";
    std::cout << "> ";
    std::getline(std::cin, message);

    if (message == "exit") break;

    int sent = sendto(clientSocket, message.c_str(), (int)message.length(), 0,
                      (sockaddr*)&serverAddr, len);

    if (sent == SOCKET_ERROR) {
        std::cout << "Gabim ne dergim: " << WSAGetLastError() << std::endl;
        continue;
    }

char buffer[BUFFER_SIZE];
int serverLen = sizeof(serverAddr);
int n = recvfrom(clientSocket, buffer, BUFFER_SIZE - 1, 0,
                 (sockaddr*)&serverAddr, &serverLen);
if (n == SOCKET_ERROR) {
    std::cout << "Gabim ne marrjen e pergjigjes: " << WSAGetLastError() << std::endl;
    } else {
        buffer[n] = '\0';
        std::cout << "Pergjigja nga serveri:\n" << buffer << std::endl;
    }
}
closesocket(clientSocket);
WSACleanup();
return 0;
