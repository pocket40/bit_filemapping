//��Ŷȭ �� ����Ŷȭ ���� �ڵ�
#include <stdlib.h>
#include<string.h>
#include <stdio.h>
typedef struct Packet
{
    char base[4096];
    size_t psize;
}Packet;

Packet* Packetizing()
{
    char name[20] = "ȫ�浿";
    int num = 9;
    int age = 8;
    Packet* packet = (Packet*)malloc(sizeof(Packet));
    packet->psize = 0;
    int len_pone = strlen(name) + 1;
    memcpy(packet->base + packet->psize, &len_pone, sizeof(int));
    packet->psize += sizeof(int);
    memcpy(packet->base + packet->psize, name, len_pone);
    packet->psize += len_pone;
    memcpy(packet->base + packet->psize, &num, sizeof(int));
    packet->psize += sizeof(int);
    memcpy(packet->base + packet->psize, &age, sizeof(int));
    packet->psize += sizeof(int);
    return packet;
}
void UnPacketizing(Packet* packet)
{
    char name[20];
    int nlen_pone;
    int num;
    int age;

    size_t usize = 0;
    memcpy(&nlen_pone, packet->base + usize, sizeof(int));
    usize += sizeof(int);
    memcpy(name, packet->base + usize, nlen_pone);
    usize += nlen_pone;
    memcpy(&num, packet->base + usize, sizeof(int));
    usize += sizeof(int);
    memcpy(&age, packet->base + usize, sizeof(int));
    usize += sizeof(int);
    if (usize == packet->psize)
    {
        printf("�̸�:%s ��ȣ:%d ����:%d\n", name, num, age);
    }
    else
    {
        printf("Un Packetizing ����...\n");
    }
}
int main()
{
    Packet* pack = Packetizing();
    UnPacketizing(pack);
    return 0;
}