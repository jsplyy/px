#include <windows.h>
#include <stdio.h>
#include <WINSOCK2.h>
#include <afxres.h>

//#pragma comment(lib,"ws2_32.lib")

int main()
{

    WSADATA wsaData;
    int sResult;
    int receCount = 10;

    sResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(sResult != 0)
    {
        printf("WSA start up fail.\r\n");
        return 1;
    }
    SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6000);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
    listen(serSocket,5);

    SOCKADDR_IN clientSock;
    int len = sizeof(SOCKADDR);

    SOCKET serConn;
    while(receCount--)
    {
        serConn = accept(serSocket,(SOCKADDR*)&clientSock, &len);
        char sendBufer[100];
        sprintf(sendBufer, "hello %s", inet_ntoa(clientSock.sin_addr));
        printf("send:%s\r\n",sendBufer);
        send(serConn,sendBufer,strlen(sendBufer)+1,0);

        char receBufer[100];
        memset(receBufer,0, sizeof(receBufer));
        recv(serConn,receBufer, sizeof(receBufer),0);
        printf("receive:%s\r\n",receBufer);
    }
    closesocket(serConn);
    WSACleanup();
    return 0;


//    MessageBox(NULL,"Hello","World",MB_OK);

    return 0;
}