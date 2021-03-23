//���� ���� ��
#include <Windows.h>
#include <stdio.h>
typedef unsigned char uchar;
typedef struct Product
{
    char title[20];//��ǰ��
    int price;//����
    int hcount;//��������
}Product;

Product* products;
void SetProduct(Product* pro, const char* title, int price, int hcount)
{
    strcpy_s(pro->title, 20, title);
    pro->price = price;
    pro->hcount = hcount;
}
void ViewProduct(Product* pro)
{
    printf("��ǰ��:%20s ����:%08d ��������:%d\n", pro->title, pro->price, pro->hcount);
}

int FindFirstEmpty(Product* pro)
{
    int i = 0;
    while (strcmp(pro[i].title, ""))
    {
        i++;
    }
    return i;
}
int FindProduct(Product* pro, int max, const char* title)
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        if (strcmp(pro[i].title, title) == 0)
        {
            break;
        }
    }
    return i;//�� ã���� �� ��ȯ�ϴ� i���� max�Դϴ�.
}
void RemoveProduct(Product* pro)
{
    memset(pro, 0, sizeof(Product));
}


void InitFileDB(const wchar_t* fname)
{
    HANDLE hFile = CreateFile(fname, //���ϸ�
        GENERIC_WRITE,//����
        0, //���� ���� ���
        0, //���� �����(�� �κ��� ������ Ŀ�� ��ü)
        CREATE_NEW,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    Product db[1000] = { 0 };
    DWORD dw;
    WriteFile(hFile, db, sizeof(db), &dw, 0);
    CloseHandle(hFile);
}
void Insert()
{
    char title[20];
    int price;
    int hcount;
    printf("�߰��� ��ǰ��:");
    gets_s(title, 20);
    //scanf_s("%s", title, 20);

    printf("����:");
    scanf_s("%d", &price);
    printf("���� ����:");
    scanf_s("%d", &hcount);
    int pos = FindFirstEmpty(products);
    if (pos == 1000) { printf("�� á���ϴ�."); return; }
    SetProduct(products + pos, title, price, hcount);
}
void Remove()
{
    char title[20];
    printf("������ ��ǰ��:");
    //scanf_s("%s", title, 20);
    gets_s(title, 20);
    int pos = FindProduct(products, 1000, title);
    if (pos == 1000) { printf("�����ϴ�."); return; }
    RemoveProduct(products + pos);
}
void Find()
{
    char title[20];
    printf("�˻��� ��ǰ��:");
    //scanf_s("%s", title, 20);
    gets_s(title, 20);
    int pos = FindProduct(products, 1000, title);
    if (pos == 1000) { printf("�����ϴ�."); return; }
    ViewProduct(products + pos);
}
void ViewAll()
{
    //   int max = FindFirstEmpty(products);
    int i = 0;
    for (i = 0; i < 1000; i++)
    {
        if (strcmp(products[i].title, ""))
        {
            ViewProduct(products + i);
        }
    }
}
void Run()
{
    ViewAll();
    Insert();
    Find();
    Remove();
    ViewAll();
}
int main()
{
    InitFileDB(TEXT("data.txt"));
    HANDLE hFile = CreateFile(TEXT("data.txt"), //���ϸ�
        GENERIC_ALL,//����
        0, //���� ���� ���
        0, //���� �����(�� �κ��� ������ Ŀ�� ��ü)
        OPEN_EXISTING,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("���� ���� ����\n");
    }
    else
    {
        HANDLE hMapping = CreateFileMapping(hFile,
            0,
            PAGE_READWRITE,
            0,
            0,
            0);
        products = (Product*)MapViewOfFile(hMapping,
            FILE_MAP_READ | FILE_MAP_WRITE,
            0,
            0,
            0);
        Run();

        //Parsing(hFile);

        UnmapViewOfFile(products);
        CloseHandle(hMapping);
    }

    CloseHandle(hFile);//Ŀ�� ��ü �ڵ��� �ݴ� API    
    return 0;
}