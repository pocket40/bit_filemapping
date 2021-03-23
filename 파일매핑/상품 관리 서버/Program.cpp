////���� ���� ������ �ڵ�
////��ǰ ���� ����
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
//    printf("��ǰ ��ȣ: %d \n", product->no);
//    printf("\t%s ����:%d ���� ����:%d\n", product->name, product->price, product->count);
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
//    printf("��ǰ ���=====\n");
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
//    //�Ʒ� �ڵ�� Ʃ�� �� �ڵ�
//    //char base[4096];   
//    //int usize = 0;
//    //ReadFile(hPipe, base, bdlen, &dw, 0);
//    //memcpy(&no, base, sizeof(int));    
//    //usize += sizeof(int);
//
//    Product* product = FindProduct(no);
//    if (product == 0)
//    {
//        printf("Ŭ���̾�Ʈ�� ������ (%d) ��ǰ ���� ��û\n", no);
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
//    printf("���� ��ǰ ��ȣ(%d)�� ��ȸ�� �Ͽ����ϴ�.\n", no);
//}
//
//int main()
//{
//    HANDLE hPipe;
//    while (true)
//    {
//        hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Test"),
//            PIPE_ACCESS_DUPLEX,//����/���� ����
//            PIPE_TYPE_BYTE,//���� ���
//            5,//���� ó���� �� �ִ� Ŭ���̾�Ʈ ��
//            4096, 4096, //�۽� �� ���� ���� ũ��
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

//��ǰ ���� ����
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
    printf("��ǰ ��ȣ: %d \n", product->no);
    printf("\t%s ����:%d ���� ����:%d\n", product->name, product->price, product->count);
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

    printf("��ǰ ���=====\n");
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
    //�Ʒ� �ڵ�� Ʃ�� �� �ڵ�
    //char base[4096];   
    //int usize = 0;
    //ReadFile(hPipe, base, bdlen, &dw, 0);
    //memcpy(&no, base, sizeof(int));    
    //usize += sizeof(int);

    Product* product = FindProduct(no);
    if (product == 0)
    {
        printf("Ŭ���̾�Ʈ�� ������ (%d) ��ǰ ���� ��û\n", no);
        return;
    }
    printf("���� ��û�� �Ծ��.\n");
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
    //�Ʒ� �ڵ�� Ʃ�� �� �ڵ�
    //char base[4096];   
    //int usize = 0;
    //ReadFile(hPipe, base, bdlen, &dw, 0);
    //memcpy(&no, base, sizeof(int));    
    //usize += sizeof(int);
    Product* product = FindProduct(no);
    char buf[4096];
    int* pbdlen = (int*)buf;
    (*pbdlen) = 0;
    printf("%d �� ��ǰ �˻� ��û�� �Գ׿�.\n");
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
        printf("���� ��ǰ�� ��û�߱���.\n");
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
    printf("���� ��ǰ ��ȣ(%d)�� ��ȸ�� �Ͽ����ϴ�.\n", no);
}

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