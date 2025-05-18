#include "../include/GamePacket.h"


GamePacket::GamePacket()
{
}

GamePacket::GamePacket(const packet &p)
{
    pkt = p;
}

GamePacket::~GamePacket()
{

}

void GamePacket::setSenderID(const char *senderId)
{
    memcpy(pkt.senderId, senderId, 16);
}

void GamePacket::setMessageType(const char *messageType)
{
    memcpy(pkt.messageType, messageType, 8);
}

packet GamePacket::getPacket()
{
    return pkt;
}

void GamePacket::setPaket(const packet &p)
{
    pkt = p;
}

void GamePacket::push(const char *str){

    size_t l = typeSequence ? strlen(typeSequence) : 0;
    if(l >= limit){
        throw std::overflow_error("typeSequence overflow when pushing string : " + std::string(str));
    }

    size_t len = strlen(str);
    if (offset + len > sizeof(pkt.messageData)) {
        throw std::overflow_error("Packet messageData overflow when pushing string: " + std::string(str));
    }
    memcpy(pkt.messageData + offset, str, len);
    offset += len;
    pushSequence(str);
    pushTypeSequence(str);
}

void GamePacket::push(const std::string &str)
{
    push(str.c_str()); 
}

char* GamePacket::getSequence()
{
    return sequence;
}

char *GamePacket::getTypeSequence(){
    return typeSequence ? typeSequence : nullptr;
}

uint32_t GamePacket::floatToNet(float f)
{
    uint32_t i;
    memcpy(&i, &f, sizeof(float));
    return htonl(i); // convert bits to network byte order
}

float GamePacket::netToFloat(uint32_t i)
{
    i = ntohl(i);
    float f;
    memcpy(&f, &i, sizeof(float));
    return f;
}

void GamePacket::popSequence()
{

}
