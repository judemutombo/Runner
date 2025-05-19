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
    free(sequence);
    free(typeSequence);
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
    uint32_t net = htonl(offset);
    pkt.messageOffset = net;
    pushSequence(str);
    pushTypeSequence(str);
}

void GamePacket::push(const std::string &str)
{
    push(str.c_str()); 
}

std::any GamePacket::pop(){
    if (strlen(typeSequence) == 0) {
        throw std::runtime_error("No types left to pop.");
    }

    char type = typeSequence[strlen(typeSequence) - 1];
    typeSequence[strlen(typeSequence) - 1] = '\0'; // Remove last type
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

    throw std::runtime_error("Unsupported type in GamePacket::pop");
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

uint64_t GamePacket::doubleToNet(double d)
{
    uint64_t i;
    memcpy(&i, &d, sizeof(double));

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    // Convert to network byte order (big endian)
    i = ((uint64_t)htonl(i & 0xFFFFFFFF) << 32) | htonl(i >> 32);
#endif

    return i;
}

double GamePacket::netToDouble(uint64_t i)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    // Convert back from network byte order
    i = ((uint64_t)ntohl(i & 0xFFFFFFFF) << 32) | ntohl(i >> 32);
#endif

    double d;
    memcpy(&d, &i, sizeof(double));
    return d;
}

size_t GamePacket::popSequence()
{
    size_t size;
    if(sequence[strlen(sequence) - 1] == ',' ){
        size = 0;
        int max = strlen(sequence) - 2;
        int counter = 0;
        while(sequence[max--] != ','){
            float val = ((size) / (10 * counter == 0 ? 1 : (10 * counter))) + (sequence[max + 1] - '0');
            if(counter != 0){
                size = (size_t) (val * (10 * counter));
            }else{
                size = (size_t) val;
            }
            ++counter;
        }
        std::cout << "size : " << size << std::endl;
        sequence[++max] = '\0';
    }else{
        size = sequence[strlen(sequence) - 1] - '0';
        sequence[strlen(sequence) - 1] = '\0';
    }

    return size;
}
