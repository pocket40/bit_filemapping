//���� ������ �̿��� �̴��� �м��� ���� �ڵ�
int main()
{
    HANDLE hFile = CreateFile(TEXT("demo.pcap"), //���ϸ�
        GENERIC_READ,//����
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