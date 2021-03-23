////서버 삭제 구현한 코드
////상품 관리 서버
//#include <Windows.h>
//#include <stdio.h>
//
//enum MsgID
//{
//    MID_REG,
//    MID_DEL,
//    MID_LST,
//    MID_FND,
//    MID_NXT
//};
//
//typedef struct MsgHead
//{
//    int msgid;
//    int bdlen;
//}MsgHead;
//
//typedef struct Product
//{
//    int no;
//    char name[256];
//    int price;
//    int count;
//}Product;
//
//
//int lastno = 0;
//int usage;
//Product products[100];
//
//void ViewProduct(Product* product)
//{
//    printf("상품 번호: %d \n", product->no);
//    printf("\t%s 가격:%d 보유 개수:%d\n", product->name, product->price, product->count);
//}
//void RegProc(HANDLE hPipe, int bdlen)
//{
//    int no;
//    int nlen_pone;
//
//    char base[4096];
//    Product* product = products + usage;
//
//    DWORD dw;
//    int usize = 0;
//    ReadFile(hPipe, base, bdlen, &dw, 0);
//    memcpy(&no, base, sizeof(int));
//    product->no = no;
//    usize += sizeof(int);
//    memcpy(&nlen_pone, base + usize, sizeof(int));
//    usize += sizeof(int);
//    memcpy(product->name, base + usize, nlen_pone);
//    usize += nlen_pone;
//    memcpy(&product->price, base + usize, sizeof(int));
//    usize += sizeof(int);
//    memcpy(&product->count, base + usize, sizeof(int));
//    usize += sizeof(int);
//
//    printf("상품 등록=====\n");
//    ViewProduct(product);
//    usage++;
//    lastno = no;
//}
//Product* FindProduct(int no)
//{
//    for (int i = 0; i < usage; i++)
//    {
//        if (products[i].no == no)
//        {
//            return products + i;
//        }
//    }
//    return 0;
//}
//void DelProc(HANDLE hPipe, int bdlen)
//{
//    int no;
//
//
//    DWORD dw;
//    ReadFile(hPipe, &no, bdlen, &dw, 0);
//    //아래 코드는 튜닝 전 코드
//    //char base[4096];   
//    //int usize = 0;
//    //ReadFile(hPipe, base, bdlen, &dw, 0);
//    //memcpy(&no, base, sizeof(int));    
//    //usize += sizeof(int);
//
//    Product* product = FindProduct(no);
//    if (product == 0)
//    {
//        printf("클라이언트가 엉뚱한 (%d) 상품 삭제 요청\n", no);
//        return;
//    }
//    usage--;
//    int index = product - products;
//    memcpy(product, product + 1, sizeof(Product) * (usage - index));
//}
//void FindProc(HANDLE hPipe, int bdlen)
//{
//
//}
//void ListProc(HANDLE hPipe, int bdlen)
//{
//
//}
//void NextProc(HANDLE hPipe, int bdlen)
//{
//    int no = lastno + 1;
//    DWORD dw;
//    WriteFile(hPipe, &no, sizeof(int), &dw, 0);
//    printf("다음 상품 번호(%d)를 조회를 하였습니다.\n", no);
//}
//
//int main()
//{
//    HANDLE hPipe;
//    while (true)
//    {
//        hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Test"),
//            PIPE_ACCESS_DUPLEX,//전송/수신 목적
//            PIPE_TYPE_BYTE,//전송 방식
//            5,//동시 처리할 수 있는 클라이언트 수
//            4096, 4096, //송신 및 수신 버퍼 크기
//            0, 0);
//        BOOL check = ConnectNamedPipe(hPipe, 0);
//        if ((check == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
//        {
//            check = true;
//        }
//        if (check)
//        {
//            MsgHead mh;
//            DWORD dw;
//            ReadFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
//            switch (mh.msgid)
//            {
//            case MID_REG: RegProc(hPipe, mh.bdlen); break;
//            case MID_DEL: DelProc(hPipe, mh.bdlen); break;
//            case MID_FND: FindProc(hPipe, mh.bdlen); break;
//            case MID_LST: ListProc(hPipe, mh.bdlen); break;
//            case MID_NXT: NextProc(hPipe, mh.bdlen); break;
//            }
//            FlushFileBuffers(hPipe);
//            DisconnectNamedPipe(hPipe);
//            CloseHandle(hPipe);
//        }
//    }
//    return 0;
//}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 
// 

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
    int bdlen;
}MsgHead;

typedef struct Product
{
    int no;
    char name[256];
    int price;
    int count;
}Product;


int lastno = 0;
int usage;
Product products[100];

void ViewProduct(Product* product)
{
    printf("상품 번호: %d \n", product->no);
    printf("\t%s 가격:%d 보유 개수:%d\n", product->name, product->price, product->count);
}
void RegProc(HANDLE hPipe, int bdlen)
{
    int no;
    int nlen_pone;

    char base[4096];
    Product* product = products + usage;

    DWORD dw;
    int usize = 0;
    ReadFile(hPipe, base, bdlen, &dw, 0);
    memcpy(&no, base, sizeof(int));
    product->no = no;
    usize += sizeof(int);
    memcpy(&nlen_pone, base + usize, sizeof(int));
    usize += sizeof(int);
    memcpy(product->name, base + usize, nlen_pone);
    usize += nlen_pone;
    memcpy(&product->price, base + usize, sizeof(int));
    usize += sizeof(int);
    memcpy(&product->count, base + usize, sizeof(int));
    usize += sizeof(int);

    printf("상품 등록=====\n");
    ViewProduct(product);
    usage++;
    lastno = no;
}
Product* FindProduct(int no)
{
    for (int i = 0; i < usage; i++)
    {
        if (products[i].no == no)
        {
            return products + i;
        }
    }
    return 0;
}
void DelProc(HANDLE hPipe, int bdlen)
{
    int no;


    DWORD dw;
    ReadFile(hPipe, &no, bdlen, &dw, 0);
    //아래 코드는 튜닝 전 코드
    //char base[4096];   
    //int usize = 0;
    //ReadFile(hPipe, base, bdlen, &dw, 0);
    //memcpy(&no, base, sizeof(int));    
    //usize += sizeof(int);

    Product* product = FindProduct(no);
    if (product == 0)
    {
        printf("클라이언트가 엉뚱한 (%d) 상품 삭제 요청\n", no);
        return;
    }
    printf("삭제 요청이 왔어요.\n");
    ViewProduct(product);
    usage--;
    int index = product - products;
    memcpy(product, product + 1, sizeof(Product) * (usage - index));
}
void FindProc(HANDLE hPipe, int bdlen)
{
    int no;
    DWORD dw;
    ReadFile(hPipe, &no, bdlen, &dw, 0);
    //아래 코드는 튜닝 전 코드
    //char base[4096];   
    //int usize = 0;
    //ReadFile(hPipe, base, bdlen, &dw, 0);
    //memcpy(&no, base, sizeof(int));    
    //usize += sizeof(int);
    Product* product = FindProduct(no);
    char buf[4096];
    int* pbdlen = (int*)buf;
    (*pbdlen) = 0;
    printf("%d 번 상품 검색 요청이 왔네요.\n");
    if (product)
    {
        memcpy(buf + (*pbdlen) + sizeof(int), &product->no, sizeof(int));
        (*pbdlen) += sizeof(int);
        int nlen_pone = strlen(product->name) + 1;
        memcpy(buf + (*pbdlen) + sizeof(int), &nlen_pone, sizeof(int));
        (*pbdlen) += sizeof(int);
        memcpy(buf + (*pbdlen) + sizeof(int), product->name, nlen_pone);
        (*pbdlen) += nlen_pone;
        memcpy(buf + (*pbdlen) + sizeof(int), &product->price, sizeof(int));
        (*pbdlen) += sizeof(int);
        memcpy(buf + (*pbdlen) + sizeof(int), &product->count, sizeof(int));
        (*pbdlen) += sizeof(int);
    }
    else
    {
        printf("없는 상품을 요청했군요.\n");
        int no = 0;
        memcpy(buf + (*pbdlen) + sizeof(int), &no, sizeof(int));
        (*pbdlen) += sizeof(int);
    }
    WriteFile(hPipe, buf, (*pbdlen) + sizeof(int), &dw, 0);

}
void ListProc(HANDLE hPipe, int bdlen)
{

}
void NextProc(HANDLE hPipe, int bdlen)
{
    int no = lastno + 1;
    DWORD dw;
    WriteFile(hPipe, &no, sizeof(int), &dw, 0);
    printf("다음 상품 번호(%d)를 조회를 하였습니다.\n", no);
}

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
            MsgHead mh;
            DWORD dw;
            ReadFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
            switch (mh.msgid)
            {
            case MID_REG: RegProc(hPipe, mh.bdlen); break;
            case MID_DEL: DelProc(hPipe, mh.bdlen); break;
            case MID_FND: FindProc(hPipe, mh.bdlen); break;
            case MID_LST: ListProc(hPipe, mh.bdlen); break;
            case MID_NXT: NextProc(hPipe, mh.bdlen); break;
            }
            FlushFileBuffers(hPipe);
            DisconnectNamedPipe(hPipe);
            CloseHandle(hPipe);
        }
    }
    return 0;
}