//파일 매핑을 이용한 이더넷 분석기 코드입니다.
//파일 매핑
//1. 파일 핸들 생성(발급)
//2. 파일 매핑 핸들 생성(발급)
//3. 매핑 뷰 설정
//4. 매핑 뷰 해제
//*3~4는 반복할 수 있음*/
//5. 파일 매핑 핸들 닫기
//6. 파일 핸들 닫기

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
PFHeader* pfh;//PCAP 파일 헤더

typedef struct PCapHeader
{
    unsigned tm_high;
    unsigned tm_low;
    unsigned cap_len;
    unsigned pac_len;
}PCapHeader, PHeader;

int pcount;//버퍼 사용 개수, 패킷 개수
int usage;//버퍼 크기
PHeader** pheaders;//버퍼 시작 주소
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
    printf("  ★★★★ ethnet header info ★★★★\n");
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
    printf("전체 패킷 개수:%d개\n", pcount);
    int i = 0;
    printf("확인할 패킷 번호:\n");
    scanf_s("%d", &i);
    if ((i <= 0) || (i > pcount)) { printf("다음 기회에..."); return; }
    uchar* ph = (uchar*)pheaders[i - 1];
    ViewEther((Ethernet*)(ph + sizeof(PHeader)));
}
int main()
{
    HANDLE hFile = CreateFile(TEXT("demo.pcap"), //파일명
        GENERIC_READ,//목적
        0, //파일 공유 모드
        0, //보안 기술자(이 부분이 있으면 커널 개체)
        OPEN_EXISTING,
        FILE_ATTRIBUTE_ARCHIVE,
        0);

    fsize = GetFileSize(hFile, 0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("파일 열기 실패\n");
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
    CloseHandle(hFile);//커널 개체 핸들을 닫는 API    
    return 0;
}