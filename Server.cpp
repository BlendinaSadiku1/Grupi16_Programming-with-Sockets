#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<winsock2.h>
#include<fstream>
#include<string>

#pragma comment(lib,"ws2_32.lib")

#define PORT 4444
#define BUFFER_SIZE 2048

const std::string IP_ADMINIT="127.0.0.1";
int main(){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    SOCKET serverSocket=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in serverAddr, clinetAddr;
    int clientLen;
    char buffer[BUFFER_SIZE];

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    serverAddr.sin_port=htons(PORT);

    if(bind(serverSocket,(sockaddr*)&serverAddr,sizeof(serverAddr))==SOCKET_ERROR){
        std::cout <<"Gabim ne Bind!"<<std::endl;
        return 1;
    }
    std::cout <<"Serveri u ndey ne porten "<<PORT <<"..." <<std::endl;
    std::cout << "Vetem Admini ("<<IP_ADMINIT<<") ka leje te shkruaj."<<std::endl;

}