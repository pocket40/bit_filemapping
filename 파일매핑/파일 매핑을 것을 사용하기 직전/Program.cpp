//파일 매핑한 것을 사용하기 직전
#include <Windows.h>
#include <stdio.h>
typedef unsigned char uchar;
typedef struct Product
{
    char title[20];//제품명
    int price;//가격
    int hcount;//보유개수
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
    printf("상품명:%20s 가격:%08d 보유개수:%d\n", pro->title, pro->price, pro->hcount);
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
    return i;//못 찾았을 때 반환하는 i값은 max입니다.
}
void RemoveProduct(Product* pro)
{
    memset(pro, 0, sizeof(Product));
}


void InitFileDB(const wchar_t* fname)
{
    HANDLE hFile = CreateFile(fname, //파일명
        GENERIC_WRITE,//목적
        0, //파일 공유 모드
        0, //보안 기술자(이 부분이 있으면 커널 개체)
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
void Run()
{

}
int main()
{
    InitFileDB(TEXT("data.txt"));
    HANDLE hFile = CreateFile(TEXT("data.txt"), //파일명
        GENERIC_ALL,//목적
        0, //파일 공유 모드
        0, //보안 기술자(이 부분이 있으면 커널 개체)
        OPEN_EXISTING,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("파일 열기 실패\n");
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
            GENERIC_READ | GENERIC_WRITE,
            0,
            0,
            0);
        Run();

        //Parsing(hFile);

        UnmapViewOfFile(products);
        CloseHandle(hMapping);
    }

    CloseHandle(hFile);//커널 개체 핸들을 닫는 API    
    return 0;
}