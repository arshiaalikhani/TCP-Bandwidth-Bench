#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    bind(listenSock,(sockaddr*)&addr, sizeof(addr));
    listen(listenSock, SOMAXCONN);
    std::cout<<"server listen on 8080...\n";

    SOCKET client = accept(listenSock, nullptr, nullptr);
    std::cout<<"client connected\n";

    const int BUF_SIZE = 64 * 1024;
    char* buf = new char[BUF_SIZE];
    memset(buf, 'A', BUF_SIZE);

    long long totalBytes = 100LL * 1024 * 1024;
    long long sent = 0;

    while(sent < totalBytes){
        int n = send(client, buf, BUF_SIZE, 0);
        if(n <= 0)break;
        sent+=n;
    }
    delete[] buf;
    closesocket(client);
    closesocket(listenSock);
    WSACleanup();
    return 0;
}
