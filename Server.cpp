#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<cstdlib>
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

    struct sockaddr_in serverAddr, clientAddr;
    int clientLen;
    char buffer[BUFFER_SIZE];

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    serverAddr.sin_port=htons(PORT);

    if(bind(serverSocket,(sockaddr*)&serverAddr,sizeof(serverAddr))==SOCKET_ERROR){
        std::cout <<"Gabim ne Bind!"<<std::endl;
        return 1;
    }
    std::cout <<"Serveri u ndez ne porten "<<PORT <<"..." <<std::endl;
    std::cout << "Vetem Admini ("<<IP_ADMINIT<<") ka leje te shkruaj dhe te ekzekutoje"<<std::endl;

    while(true){
        clientLen=sizeof(clientAddr);
        memset(buffer,0,BUFFER_SIZE);

        int n=recvfrom(serverSocket, buffer, BUFFER_SIZE-1,0,(sockaddr*)&clientAddr,&clientLen);
        if(n == SOCKET_ERROR) continue;

        buffer[n]='\0';
        std::string msg(buffer);
        std::string response;

        std::string senderIP=inet_ntoa(clientAddr.sin_addr);
        std::cout <<"Mesazh nga ["<< senderIP <<"]:" << msg << std::endl;

        if(msg.rfind("read|",0)==0){
            std::string filename=msg.substr(5);
            std::ifstream file(filename);
            if(file.is_open()){
                std::string content((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
                response=content.empty() ? "File eshte bosh!" : content;
                file.close();
            }else{
                response="Gabim File nuk ekziston!";
            }
        }

       else if (msg.rfind("write|", 0) == 0) {
            
            if (senderIP != IP_ADMINIT) {
                response = "GABIM: Ju nuk keni autorizim per te shkruar! Vetem Admini lejohet.";
                std::cout << "Tentim i paautorizuar per shkrim nga: " << senderIP << std::endl;
             }
            else {
                size_t first = msg.find("|");
                size_t second = msg.find("|", first + 1);

                if (second != std::string::npos) {
                    std::string filename = msg.substr(first + 1, second - first - 1);
                    std::string text = msg.substr(second + 1);


                    std::ofstream file(filename, std::ios::app);
                    if (file.is_open()) {
                        file << text << "\n";
                        file.flush();
                        file.close();
                        response = "Sukses: U shkrua me sukses nga Admini!";
                        std::cout << "Admini shkruajti ne " << filename << std::endl;
                    } else {
                        response = "Gabim: Serveri nuk mund ta hapi skedarin!";
                    }
                } else {
                    response = "Format gabim! write|file.txt|teksti";
                }
            }
        }

        else if (msg.rfind("execute|", 0) == 0) {

            if (senderIP != IP_ADMINIT) {
                response = "GABIM: Ju nuk keni autorizim per te ekzekutuar! Vetem Admini lejohet.";
                std::cout << "Tentim i paautorizuar per execute nga: " << senderIP << std::endl;
            }
            else {
                std::string filename = msg.substr(8);

                int result = system(filename.c_str());

                if (result == 0) {
                    response = "Sukses: File u ekzekutua me sukses nga Admini!";
                    std::cout << "Admini ekzekutoi file-in: " << filename << std::endl;
                } else {
                    response = "Gabim: File nuk mund te ekzekutohet!";
                }
            }
        }
        else if (msg.rfind("execute|", 0) == 0) {

            if (senderIP != IP_ADMINIT) {
                response = "GABIM: Ju nuk keni autorizim per te ekzekutuar! Vetem Admini lejohet.";
                std::cout << "Tentim i paautorizuar per execute nga: " << senderIP << std::endl;
            }
            else {
                std::string filename = msg.substr(8);

                int result = system(filename.c_str());

                if (result == 0) {
                    response = "Sukses: File u ekzekutua me sukses nga Admini!";
                    std::cout << "Admini ekzekutoi file-in: " << filename << std::endl;
                } else {
                    response = "Gabim: File nuk mund te ekzekutohet!";
                }
            }
        }
      


        else {
            response = "Komande e panjohur!";
        }

        sendto(serverSocket, response.c_str(), (int)response.length(), 0, (sockaddr*)&clientAddr, clientLen);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}