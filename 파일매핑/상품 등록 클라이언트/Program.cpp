////상품 등록 클라이언트 코드입니다.
//#include <Windows.h>
//#include <stdio.h>
//enum MsgID
//{
//    MID_REG,
//    MID_DEL,
//    MID_LST,
//    MID_FND,
//    MID_NXT
//};
//typedef struct MsgHead
//{
//    int msgid;
//    int bdlen;
//}MsgHead;
//
//int NextProductNo()
//{
//    HANDLE hPipe;
//    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
//        GENERIC_WRITE | GENERIC_READ,
//        0, 0,
//        OPEN_EXISTING, 0, 0);
//
//    MsgHead mh;
//    mh.msgid = MID_NXT;
//    mh.bdlen = 0;
//    DWORD dw;
//    WriteFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
//    int no;
//    ReadFile(hPipe, &no, sizeof(int), &dw, 0);
//
//    CloseHandle(hPipe);
//    return no;
//}
//void RegProduct(int no, const char* name, int price, int count)
//{
//    HANDLE hPipe;
//    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
//        GENERIC_WRITE | GENERIC_READ,
//        0, 0,
//        OPEN_EXISTING, 0, 0);
//
//    char buf[4096];
//    MsgHead* mh = (MsgHead*)buf;
//    mh->msgid = MID_REG;
//    mh->bdlen = 0;
//    char* pbuf = buf + sizeof(MsgHead);
//    memcpy(pbuf + mh->bdlen, &no, sizeof(int));
//    mh->bdlen += sizeof(int);
//    int nlen_pone = strlen(name) + 1;
//    memcpy(pbuf + mh->bdlen, &nlen_pone, sizeof(int));
//    mh->bdlen += sizeof(int);
//    memcpy(pbuf + mh->bdlen, name, nlen_pone);
//    mh->bdlen += nlen_pone;
//    memcpy(pbuf + mh->bdlen, &price, sizeof(int));
//    mh->bdlen += sizeof(int);
//    memcpy(pbuf + mh->bdlen, &count, sizeof(int));
//    mh->bdlen += sizeof(int);
//    DWORD dw;
//    WriteFile(hPipe, buf, sizeof(MsgHead) + mh->bdlen, &dw, 0);
//    CloseHandle(hPipe);
//}
//int DelProc(int no)
//{
//    HANDLE hPipe;
//    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
//        GENERIC_WRITE | GENERIC_READ,
//        0, 0,
//        OPEN_EXISTING, 0, 0);
//
//    char buf[4096];
//    MsgHead* mh = (MsgHead*)buf;
//    mh->msgid = MID_REG;
//    mh->bdlen = 0;
//    char* pbuf = buf + sizeof(MsgHead);
//    memcpy(pbuf + mh->bdlen, &no, sizeof(int));
//    mh->bdlen += sizeof(int);
//
//    DWORD dw;
//    WriteFile(hPipe, buf, sizeof(MsgHead) + mh->bdlen, &dw, 0);
//    FlushFileBuffers(hPipe);
//    CloseHandle(hPipe);
//}
//#include <stdio.h>
//#include <conio.h>
//#pragma warning(disable:4996)
//enum MyScanKey
//{
//    F1=0x3b0000,
//    F2=0x3c0000,
//    F3=0x3c0000,
//    ESC=0x1b,
//}
//
//
//int getscankey()
//{
//    int key = getch();
//    if (key == 0) || (key == 224)
//    {
//        return getch() << 16;
//    }
//    return key;
//}
//int SelectMenu() 
//{
//    system("cls");
//    printf("menu\n");
//    printf("F1:상품 등록\n");
//    printf("F1:상품 제거\n");
//    printf("F1:상품 검색\n");
//    return getscankey();
//}
//void RegProc()
//{
//    char title[256];
//    int price;
//    int count;
//
//    int no = NextProductNo();
//    printf("등록할 상품 명.");
//    gets_s(title, 256);
//    printf("가격");
//    scanf_s("%d", &price);
//    printf("개수");
//    scanf_s("%d", &count);
//    RegProduct(no, title, price, count);
//}
//void RemoveProc()
//{
//    int no = 0;
//    printf("삭제할 상품 번호");
//    scanf_s("%d", &no);
//    DelProc(no);
//}
//
//
//
//int main()
//{
//    //system("mspaint");// 시스템한수안에 있는 프로그램을 실행 시킨다.
//    //printf("1\n");
//    //system("notepad");
//    //printf("2");
//    //system("")
//
//    /*for (int i = 0; i < 10; i++)
//    {
//        int key = 0;
//        key = getch();
//        printf("%d\n", key);
//    }*/
//    //int key = 0;
//    //while ((key = SelectMenu()) != ESC)
//    //{
//    //    switch (key)
//    //    {
//    //    case F1:RegProc(); break;
//    //    case F2:RemoveProc(); break;
//    //    case F3:FindProc(); break;
//    //    default: printf("잘못 선택하였습니다.\n"); break;
//    //    }
//    //    printf("아무 키나 누르세요.\n");
//    //    getch(); // null 버퍼링 
//    //    
//    //}
//    /*int no = NextProductNo();
//    int sno = no;
//    Sleep(10);
//    RegProduct(no, "C언어", 12000, 20);
//    Sleep(10);
//    no = NextProductNo();
//    Sleep(10);
//    RegProduct(no, "고구마는 맛있다.", 22000, 10);
//    Sleep(10);
//    DelProc(sno);*/
//    return 0;
//}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//상품 등록 클라이언트 코드입니다.
//#include <Windows.h>
//#include <stdio.h>
//enum MsgID
//{
//    MID_REG,
//    MID_DEL,
//    MID_LST,
//    MID_FND,
//    MID_NXT
//};
//typedef struct MsgHead
//{
//    int msgid;
//    int bdlen;
//}MsgHead;
//
//int NextProductNo()
//{
//    HANDLE hPipe;
//    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
//        GENERIC_WRITE | GENERIC_READ,
//        0, 0,
//        OPEN_EXISTING, 0, 0);
//
//    MsgHead mh;
//    mh.msgid = MID_NXT;
//    mh.bdlen = 0;
//    DWORD dw;
//    WriteFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
//    int no;
//    ReadFile(hPipe, &no, sizeof(int), &dw, 0);
//
//    CloseHandle(hPipe);
//    return no;
//}
//void RegProduct(int no, const char* name, int price, int count)
//{
//    HANDLE hPipe;
//    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
//        GENERIC_WRITE | GENERIC_READ,
//        0, 0,
//        OPEN_EXISTING, 0, 0);
//
//    char buf[4096];
//    MsgHead* mh = (MsgHead*)buf;
//    mh->msgid = MID_REG;
//    mh->bdlen = 0;
//    char* pbuf = buf + sizeof(MsgHead);
//    memcpy(pbuf + mh->bdlen, &no, sizeof(int));
//    mh->bdlen += sizeof(int);
//    int nlen_pone = strlen(name) + 1;
//    memcpy(pbuf + mh->bdlen, &nlen_pone, sizeof(int));
//    mh->bdlen += sizeof(int);
//    memcpy(pbuf + mh->bdlen, name, nlen_pone);
//    mh->bdlen += nlen_pone;
//    memcpy(pbuf + mh->bdlen, &price, sizeof(int));
//    mh->bdlen += sizeof(int);
//    memcpy(pbuf + mh->bdlen, &count, sizeof(int));
//    mh->bdlen += sizeof(int);
//    DWORD dw;
//    WriteFile(hPipe, buf, sizeof(MsgHead) + mh->bdlen, &dw, 0);
//    CloseHandle(hPipe);
//}
//int main()
//{
//    int no = NextProductNo();
//    Sleep(10);
//    RegProduct(no, "C언어", 12000, 20);
//    Sleep(10);
//    no = NextProductNo();
//    Sleep(10);
//    RegProduct(no, "고구마는 맛있다.", 22000, 10);
//}

//---------------------------- ---------------------------------------------------------- ---------------------------------------------------------- ------------------------------
//메뉴 있는 클라이언트 작성 중
//상품 등록 클라이언트
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
    int bdlen;
}MsgHead;

int NextProductNo()
{
    HANDLE hPipe;
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
        GENERIC_WRITE | GENERIC_READ,
        0, 0,
        OPEN_EXISTING, 0, 0);

    MsgHead mh;
    mh.msgid = MID_NXT;
    mh.bdlen = 0;
    DWORD dw;
    WriteFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
    int no;
    ReadFile(hPipe, &no, sizeof(int), &dw, 0);

    CloseHandle(hPipe);
    return no;
}
void RegProduct(int no, const char* name, int price, int count)
{
    HANDLE hPipe;
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
        GENERIC_WRITE | GENERIC_READ,
        0, 0,
        OPEN_EXISTING, 0, 0);

    char buf[4096];
    MsgHead* mh = (MsgHead*)buf;
    mh->msgid = MID_REG;
    mh->bdlen = 0;
    char* pbuf = buf + sizeof(MsgHead);
    memcpy(pbuf + mh->bdlen, &no, sizeof(int));
    mh->bdlen += sizeof(int);
    int nlen_pone = strlen(name) + 1;
    memcpy(pbuf + mh->bdlen, &nlen_pone, sizeof(int));
    mh->bdlen += sizeof(int);
    memcpy(pbuf + mh->bdlen, name, nlen_pone);
    mh->bdlen += nlen_pone;
    memcpy(pbuf + mh->bdlen, &price, sizeof(int));
    mh->bdlen += sizeof(int);
    memcpy(pbuf + mh->bdlen, &count, sizeof(int));
    mh->bdlen += sizeof(int);
    DWORD dw;
    WriteFile(hPipe, buf, sizeof(MsgHead) + mh->bdlen, &dw, 0);
    FlushFileBuffers(hPipe);
    CloseHandle(hPipe);
}
void DelProc(int no)
{
    HANDLE hPipe;
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
        GENERIC_WRITE | GENERIC_READ,
        0, 0,
        OPEN_EXISTING, 0, 0);

    char buf[4096];
    MsgHead* mh = (MsgHead*)buf;
    mh->msgid = MID_DEL;
    mh->bdlen = 0;
    char* pbuf = buf + sizeof(MsgHead);
    memcpy(pbuf + mh->bdlen, &no, sizeof(int));
    mh->bdlen += sizeof(int);

    DWORD dw;
    WriteFile(hPipe, buf, sizeof(MsgHead) + mh->bdlen, &dw, 0);
    FlushFileBuffers(hPipe);
    CloseHandle(hPipe);
}
void FindProduct(int no)
{
    HANDLE hPipe;
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Test"),
        GENERIC_WRITE | GENERIC_READ,
        0, 0,
        OPEN_EXISTING, 0, 0);

    char buf[4096];
    MsgHead* mh = (MsgHead*)buf;
    mh->msgid = MID_FND;
    mh->bdlen = 0;
    char* pbuf = buf + sizeof(MsgHead);
    memcpy(pbuf + mh->bdlen, &no, sizeof(int));
    mh->bdlen += sizeof(int);

    DWORD dw;
    WriteFile(hPipe, buf, sizeof(MsgHead) + mh->bdlen, &dw, 0);
    //char buf[4096];
    int blen = 0;
    ReadFile(hPipe, &blen, sizeof(blen), &dw, 0);
    ReadFile(hPipe, buf, blen, &dw, 0);
    int usize = 0;
    int fno;
    memcpy(&fno, buf + usize, sizeof(int));
    usize += sizeof(int);
    if (fno != no)
    {
        printf("%d번은 존재하지 않는 상품이라고 하네요.\n", no);
    }
    else
    {
        char name[256];
        int nlen_pone;
        int price;
        int count;
        memcpy(&nlen_pone, buf + usize, sizeof(int));
        usize += sizeof(int);
        memcpy(name, buf + usize, nlen_pone);
        usize += nlen_pone;
        memcpy(&price, buf + usize, sizeof(int));
        usize += sizeof(int);
        memcpy(&count, buf + usize, sizeof(int));
        usize += sizeof(int);
        printf("상품명:%s 가격:%d 개수:%d\n", name, price, count);
    }
    CloseHandle(hPipe);
}
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
enum MyScanKey
{
    F1 = 0x3b0000,
    F2 = 0x3c0000,
    F3 = 0x3d0000,
    ESC = 0x1b
};

int getscankey()
{
    int key = getch();
    if ((key == 0) || (key == 224))
    {
        return getch() << 16;
    }
    return key;
}
int SelectMenu()
{
    system("cls");
    printf("Menu\n");
    printf("F1: 상품 등록\n");
    printf("F2: 상품 제거\n");
    printf("F3: 상품 검색\n");
    return getscankey();
}
void RegProc()
{
    char title[256];
    int price;
    int count;

    int no = NextProductNo();
    printf("%d th\n", no);
    printf("등록할 상품 명:");
    gets_s(title, 256);
    printf("가격:");
    scanf_s("%d", &price);
    printf("개수:");
    scanf_s("%d", &count);
    RegProduct(no, title, price, count);
    rewind(stdin);
}
void RemoveProc()
{
    int no = 0;
    printf("삭제할 상품 번호:");
    scanf_s("%d", &no);
    rewind(stdin);
    DelProc(no);
}
void FindProc()
{
    int no = 0;
    printf("검색할 상품 번호:");
    scanf_s("%d", &no);
    rewind(stdin);
    FindProduct(no);
}
int main()
{
    int key = 0;
    while ((key = SelectMenu()) != ESC)
    {
        switch (key)
        {
        case F1: RegProc(); break;
        case F2: RemoveProc(); break;
        case F3: FindProc(); break;
        default: printf("잘못 선택하였습니다.\n"); break;
        }
        printf("아무 키나 누르세요.\n");
        getch();
    }
    return 0;
}