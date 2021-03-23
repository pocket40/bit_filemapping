#include <Windows.h>
#include <stdio.h>

//상품 관리 서버
#include <Windows.h>
#include <stdio.h>

enum MsgID
{
    MID_REG,
    MID_DEL,
    MID_LST,
    MID_FND,
    MID_NXT
};

typedef struct MsgHead
{
    int msgid;
    int dblen;
}MsgHead;

int NextProductNo(HANDLE hPipe)
{
    MsgHead mh;
    mh.msgid = MID_NXT;
    mh.dblen = 0;
    DWORD dw;
    WriteFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
    int no;
    ReadFile(hPipe, &no, sizeof(int), &dw, 0);
    return no;
}
void RegProduct(HANDLE hPipe, int no, const char* name, int price, int count)
{
    MsgHead mh;
    mh.msgid = MID_REG;
    mh.dblen = 0;


    char buf[4096];
    MsgHead* mh = (MsgHead*)buf;
    mh->msgid = MID_RED;
    mh->bdlen = 0;
    char* pbuf = buf + sizeof(MsgHead);
    memcpy(buf + mh.dblen, &no, sizeof(int));
    mh.dblen += sizeof(int);
    int nlen_pone = strlen(name) + 1;
    memcpy(buf + mh.dblen, &nlen_pone, sizeof(int));
    mh.dblen += sizeof(int);
    memcpy(buf + mh.dblen, name, nlen_pone);
    mh.dblen += nlen_pone;
    memcpy(buf + mh.dblen, &price, sizeof(int));
    mh->bdlen += sizeof(int);
    memcpy(pbuf + mh->bdlen, &count, sizeof(int));
    mh->bdlen += sizeof(int);
    DWORD dw;
    WriteFile(hPipe, buf, sizeof(MsgHead) + mh->bdlen, &dw, 0);
}
int main()
{
    HANDLE hPipe;
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
        GENERIC_WRITE | GENERIC_READ,
        0, 0,
        OPEN_EXISTING, 0, 0);
    char buf[256];
    DWORD dw;
    while (true)
    {
        printf("전송할 메시지:");
        gets_s(buf, 256);
        WriteFile(hPipe, buf, 256, &dw, 0);
        if (strcmp(buf, "exit") == 0)
        {
            break;
        }
        ReadFile(hPipe, buf, 256, &dw, 0);
        puts(buf);
    }
    CloseHandle(hPipe);
    return 0;
}