//���� ������ �̿��� �̴��� �м��� �ڵ��Դϴ�.
//���� ����
//1. ���� �ڵ� ����(�߱�)
//2. ���� ���� �ڵ� ����(�߱�)
//3. ���� �� ����
//4. ���� �� ����
//*3~4�� �ݺ��� �� ����*/
//5. ���� ���� �ڵ� �ݱ�
//6. ���� �ڵ� �ݱ�

#include <WinSock2.h>
#pragma comment(lib,"ws2_32")
#include <Windows.h>
#include <stdio.h>
#pragma pack(1)
#define PCAP_MAGIC 0xa1b2c3d4
typedef unsigned char uchar;
typedef unsigned long ulong;

typedef struct PCapFileHeader
{
    unsigned int magic;
    int version;
    int tz;
    int ts;
    int snap_len;
    int link_type;
}PCapFileHeader, PFHeader;
PFHeader* pfh;//PCAP ���� ���

typedef struct PCapHeader
{
    unsigned tm_high;
    unsigned tm_low;
    unsigned cap_len;
    unsigned pac_len;
}PCapHeader, PHeader;

int pcount;//���� ��� ����, ��Ŷ ����
int usage;//���� ũ��
PHeader** pheaders;//���� ���� �ּ�
ulong fsize;

typedef unsigned short ushort;
typedef struct Ethernet
{
    uchar dest[6];
    uchar src[6];
    ushort type;
}Ethernet;
void ViewMacAddr(uchar* addr)
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        printf("%02X:", addr[i]);
    }
    printf("%02X\n", addr[i]);
}
void ViewEther(Ethernet* eth)
{
    printf("  �ڡڡڡ� ethnet header info �ڡڡڡ�\n");
    printf("\tdest:");
    ViewMacAddr(eth->dest);
    printf("\tsrc:");
    ViewMacAddr(eth->src);
    printf("\ttype:%#X\n", ntohs(eth->type));
}


int IsFull()
{
    return usage == pcount;
}
void Extend()
{
    if (usage == 0)
    {
        usage = 1;
    }
    else
    {
        usage *= 2;
    }
    pheaders = (PHeader**)realloc(pheaders, sizeof(PHeader*) * usage);
}
void PreParsing(uchar* data)
{
    while (fsize > 0)
    {
        if (IsFull())
        {
            Extend();
        }
        pheaders[pcount] = (PHeader*)data;
        data += sizeof(PHeader) + pheaders[pcount]->cap_len;
        fsize -= sizeof(PHeader) + pheaders[pcount]->cap_len;
        pcount++;
    }
}
void Run(uchar* data)
{
    pfh = (PCapFileHeader*)data;
    if (pfh->magic != PCAP_MAGIC)
    {
        return;
    }
    data += sizeof(PCapFileHeader);
    fsize -= sizeof(PCapFileHeader);
    PreParsing(data);
    printf("��ü ��Ŷ ����:%d��\n", pcount);
    int i = 0;
    printf("Ȯ���� ��Ŷ ��ȣ:\n");
    scanf_s("%d", &i);
    if ((i <= 0) || (i > pcount)) { printf("���� ��ȸ��..."); return; }
    uchar* ph = (uchar*)pheaders[i - 1];
    ViewEther((Ethernet*)(ph + sizeof(PHeader)));
}
int main()
{
    HANDLE hFile = CreateFile(TEXT("demo.pcap"), //���ϸ�
        GENERIC_READ,//����
        0, //���� ���� ���
        0, //���� �����(�� �κ��� ������ Ŀ�� ��ü)
        OPEN_EXISTING,
        FILE_ATTRIBUTE_ARCHIVE,
        0);

    fsize = GetFileSize(hFile, 0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("���� ���� ����\n");
    }
    else
    {
        HANDLE hMapping = CreateFileMapping(hFile,
            0,
            PAGE_READONLY,
            0,
            0,
            0);
        uchar* data = (uchar*)MapViewOfFile(hMapping,
            FILE_MAP_READ,
            0,
            0,
            0);

        Run(data);

        UnmapViewOfFile(data);
        CloseHandle(hMapping);
    }
    CloseHandle(hFile);//Ŀ�� ��ü �ڵ��� �ݴ� API    
    return 0;
}