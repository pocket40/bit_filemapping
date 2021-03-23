//패킷화 및 언패킷화 데모 코드
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
    char name[20] = "홍길동";
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
        printf("이름:%s 번호:%d 나이:%d\n", name, num, age);
    }
    else
    {
        printf("Un Packetizing 실패...\n");
    }
}
int main()
{
    Packet* pack = Packetizing();
    UnPacketizing(pack);
    return 0;
}