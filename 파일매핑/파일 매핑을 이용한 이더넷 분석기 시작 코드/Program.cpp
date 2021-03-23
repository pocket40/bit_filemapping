//파일 매핑을 이용한 이더넷 분석기 시작 코드
int main()
{
    HANDLE hFile = CreateFile(TEXT("demo.pcap"), //파일명
        GENERIC_READ,//목적
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