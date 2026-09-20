#define _WIN32_WINNT 0x0600

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client, (sockaddr*)&server, sizeof(server));
    std::cout<<"connected to server\n";

    const int BUF_SIZE = 64*1024;
    char* buf = new char[BUF_SIZE];

    long long totalByte = 100LL * 1024 * 1024;
    long long recevied = 0;

    while(recevied < totalByte){
        int n = recv(client, buf, BUF_SIZE, 0);
        if(n <= 0)break;
        recevied += n;
    }
    std::cout<<"received "<< (recevied / 1024 / 1024) <<" MB\n";

    delete[] buf;
    closesocket(client);
    WSACleanup();
    return 0;
}
