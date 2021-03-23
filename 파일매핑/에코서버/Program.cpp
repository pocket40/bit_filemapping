//에코 서버
#include <Windows.h>
#include <stdio.h>
int main()
{
    HANDLE hPipe;
    while (true)
    {
        hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Test"),
            PIPE_ACCESS_DUPLEX,//전송/수신 목적
            PIPE_TYPE_BYTE,//전송 방식
            5,//동시 처리할 수 있는 클라이언트 수
            4096, 4096, //송신 및 수신 버퍼 크기
            0, 0);
        BOOL check = ConnectNamedPipe(hPipe, 0);
        if ((check == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
        {
            check = true;
        }
        if (check)
        {
            char buf[256];
            DWORD dw;
            while (true)
            {
                ReadFile(hPipe, buf, 256, &dw, 0);
                if (strcmp(buf, "exit") == 0)
                {
                    break;
                }
                printf("수신한 메시지:%s\n", buf);
                WriteFile(hPipe, buf, 256, &dw, 0);
            }
            DisconnectNamedPipe(hPipe);
            CloseHandle(hPipe);
        }
    }
    return 0;
}