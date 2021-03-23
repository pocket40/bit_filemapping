//���� ����
#include <Windows.h>
#include <stdio.h>
int main()
{
    HANDLE hPipe;
    while (true)
    {
        hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Test"),
            PIPE_ACCESS_DUPLEX,//����/���� ����
            PIPE_TYPE_BYTE,//���� ���
            5,//���� ó���� �� �ִ� Ŭ���̾�Ʈ ��
            4096, 4096, //�۽� �� ���� ���� ũ��
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
                printf("������ �޽���:%s\n", buf);
                WriteFile(hPipe, buf, 256, &dw, 0);
            }
            DisconnectNamedPipe(hPipe);
            CloseHandle(hPipe);
        }
    }
    return 0;
}