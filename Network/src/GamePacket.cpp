#include "../include/GamePacket.h"

GamePacket::GamePacket() :
    itemCount(0)
{
    pkt.itemCount = htons(itemCount);
}

GamePacket::GamePacket(const packet &p)
{
    pkt = p;
    itemCount = ntohs(p.itemCount);
    memcpy(sequence, pkt.sequence, sizeof(pkt.sequence));
    memcpy(typeSequence, pkt.typeSequence, sizeof(pkt.typeSequence));
    offset = ntohs(pkt.messageOffset);

}

GamePacket::~GamePacket()
{
}

void GamePacket::setSenderID(const char *senderId)
{
    memcpy(pkt.senderId, senderId, MAX_SENDER_ID_SIZE);
}

void GamePacket::setMessageType(const char *messageType)
{
    memcpy(pkt.messageType, messageType, MAX_TYPE_SIZE);
}

packet GamePacket::getPacket()
{
    return pkt;
}

void GamePacket::setPaket(const packet &p)
{
    pkt = p;
    itemCount = ntohs(p.itemCount);
    memcpy(sequence, pkt.sequence, sizeof(pkt.sequence));
    memcpy(typeSequence, pkt.typeSequence, sizeof(pkt.typeSequence));
    offset = ntohs(pkt.messageOffset);
}

void GamePacket::push(const char *str){

    if(itemCount >= limit){
        throw std::overflow_error("typeSequence overflow when pushing string : " + std::string(str));
    }

    size_t len = strlen(str);
    if (offset + len > sizeof(pkt.messageData)) {
        throw std::overflow_error("Packet messageData overflow when pushing string: " + std::string(str));
    }
    memcpy(pkt.messageData + offset, str, len);
    offset += len;
    pkt.messageOffset = htonl(offset);
    pushSequence(str);
    pushTypeSequence(str);
    
    itemCount++;
    pkt.itemCount = htons(itemCount);
    pkt.packetLength = htons(sizeof(pkt));
}

void GamePacket::push(const std::string &str)
{
    push(str.c_str()); 
}

std::any GamePacket::pop(){
    if (itemCount == 0) {
        throw std::runtime_error("No types left to pop.");
    }

    char type = typeSequence[--itemCount];
    typeSequence[itemCount] = 0; 
    size_t dataSize = popSequence(); 
    offset -= dataSize; 

    //std::cout << type << " : " << dataSize << std::endl;

    if (type == 'I') {
        uint32_t net;
        memcpy(&net, pkt.messageData + offset, sizeof(uint32_t));
        int value = ntohl(net);
        return std::any(value);
    } else if (type == 'S') {
        std::string value(reinterpret_cast<char*>(pkt.messageData + offset), dataSize);
        return std::any(value);
    }else if (type == 'D') {
        uint64_t net;
        memcpy(&net, pkt.messageData + offset, sizeof(uint64_t));
        double value = netToDouble(net);
        return std::any(value);
    }else if (type == 'F') {
        uint32_t net;
        memcpy(&net, pkt.messageData + offset, sizeof(uint32_t));
        float value = netToFloat(net);
        return std::any(value);
    }else if (type == 'B') {
        uint8_t net;
        memcpy(&net, pkt.messageData + offset, sizeof(uint8_t));
        bool value = static_cast<bool>(net);
        return std::any(value);
    }else if (type == 'C') {
        uint8_t net;
        memcpy(&net, pkt.messageData + offset, sizeof(uint8_t));
        char value = static_cast<char>(net);
        return std::any(value);
    }

    std::string error {"Unsupported type("};
    error += type;
    error += ") in GamePacket::pop";
    throw std::runtime_error(error);
}

std::string GamePacket::getSequence()
{
    std::string s{""};
    for (size_t i = 0; i < itemCount; i++)
    {
        s += std::to_string(sequence[i]);
    }
    
    return s;
}

std::string GamePacket::getTypeSequence(){
    std::string s{""};
    for (size_t i = 0; i < itemCount; i++)
    {
        s += typeSequence[i];
    }
    
    return s;
}

uint32_t GamePacket::floatToNet(float f)
{
    uint32_t i;
    memcpy(&i, &f, sizeof(float));
    return htonl(i); 
}

float GamePacket::netToFloat(uint32_t i)
{
    i = ntohl(i);
    float f;
    memcpy(&f, &i, sizeof(float));
    return f;
}

uint64_t GamePacket::doubleToNet(double d)
{
    uint64_t i;
    memcpy(&i, &d, sizeof(double));

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    
    i = ((uint64_t)htonl(i & 0xFFFFFFFF) << 32) | htonl(i >> 32);
#endif

    return i;
}

double GamePacket::netToDouble(uint64_t i)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    
    i = ((uint64_t)ntohl(i & 0xFFFFFFFF) << 32) | ntohl(i >> 32);
#endif

    double d;
    memcpy(&d, &i, sizeof(double));
    return d;
}

size_t GamePacket::popSequence()
{
    size_t size;
    size = sequence[itemCount];

    return size;
}
