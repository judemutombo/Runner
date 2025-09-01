#ifndef GAMEPACKET_H
#define GAMEPACKET_H


#ifdef _WIN32
    #include <winsock2.h>
    #include <Ws2tcpip.h>
#endif

#ifdef __linux__
    #include <arpa/inet.h>
#endif
#include <stdint.h>
#include <string.h>
#include <type_traits>
#include <stdexcept>
#include <iostream>
#include <any>
#include "packet.h"
#include "packetConfig.h"

class GamePacket
{
public:
    GamePacket();
    GamePacket(const Packet& p);
    ~GamePacket();
    void setSenderID(const char* senderId);
    void setMessageType(const char* messageType);
    Packet getPacket();
    void setPaket(const Packet& p);
    template<typename T> void push(const T& value);
    void push(const char* str);
    void push(const std::string& str);
    std::any pop();
    std::string getSequence();
    std::string getTypeSequence();
    
private:
    Packet pkt;
    uint32_t floatToNet(float f);
    float netToFloat(uint32_t i);
    uint64_t doubleToNet(double d);
    double netToDouble(uint64_t i);
    size_t offset = 0;
    uint16_t sequence[MAX_SEQ_SIZE];
    char typeSequence[MAX_TYPE_SEQ_SIZE];
    size_t itemCount;
    template<typename T> void pushTypeSequence(const T& value);
    template<typename T> void pushSequence(const T& value);
    size_t popSequence();
    uint16_t limit = LIMIT_TYPE_SEQ;
};

template<typename T> 
inline void GamePacket::push(const T& value){
    static_assert(std::is_arithmetic<T>::value, "Only arithmetic types are supported");

    if (offset + sizeof(T) > MAX_MESSAGE_SIZE) {
        throw std::overflow_error("Packet messageData overflow when pushing arithmetic : " + std::to_string(value));
    }

    
    if(itemCount >= limit){
        throw std::overflow_error("typeSequence overflow when pushing arithmetic : " + std::to_string(value));
    }
    
    if constexpr (std::is_same<T, float>::value) {
        uint32_t net = floatToNet(value);
        memcpy(pkt.messageData + offset, &net, sizeof(net));
    }else if constexpr (std::is_same<T, double>::value) {
        uint64_t net = doubleToNet(value);
        memcpy(pkt.messageData + offset, &net, sizeof(net));
    } else if constexpr (sizeof(T) == 2) {
        uint16_t net = htons(value);
        memcpy(pkt.messageData + offset, &net, sizeof(net));
    } else if constexpr (sizeof(T) == 4) {
        uint32_t net = htonl(value);
        memcpy(pkt.messageData + offset, &net, sizeof(net));
    } else if constexpr (sizeof(T) == 8) {
        uint64_t v = static_cast<uint64_t>(value);
        uint64_t net = ((uint64_t)htonl(v & 0xFFFFFFFF) << 32) | htonl(v >> 32);
        memcpy(pkt.messageData + offset, &net, sizeof(net));
    } else {
        memcpy(pkt.messageData + offset, &value, sizeof(T));
    }
    offset += sizeof(T);
    pkt.messageOffset = htonl(offset);
    pushSequence(value);
    pushTypeSequence(value);

    itemCount++;
    pkt.itemCount = htons(itemCount);
    pkt.packetLength = htons(sizeof(pkt));
}

template <typename T>
inline void GamePacket::pushTypeSequence(const T &value)
{    
    if constexpr (std::is_same<T, int>::value){
        typeSequence[itemCount] = 'I';
        pkt.typeSequence[itemCount] = 'I';
    }else if constexpr (std::is_same<T, float>::value){
        typeSequence[itemCount] = 'F';
        pkt.typeSequence[itemCount] = 'F';
    }else if constexpr (std::is_same<T, double>::value){
        typeSequence[itemCount] = 'D';
        pkt.typeSequence[itemCount] = 'D';
    }else if constexpr (std::is_same<T, bool>::value){
        typeSequence[itemCount] = 'B';
         pkt.typeSequence[itemCount] = 'B';
    }else if constexpr (
        std::is_same<T, char*>::value ||
        std::is_same<T, const char*>::value ||
        std::is_same<T, char[]>::value ||
        std::is_same<T, const char[]>::value
    ){
        typeSequence[itemCount] = 'S';
        pkt.typeSequence[itemCount] = 'S';
    }else if constexpr (std::is_same<T, char>::value){
        typeSequence[itemCount] = 'C';
        pkt.typeSequence[itemCount] = 'C';
    }else{
        typeSequence[itemCount] = '?'; 
        pkt.typeSequence[itemCount] = '?';
    }
}

template <typename T>
inline void GamePacket::pushSequence(const T& value) {

 
    if constexpr (
        std::is_same_v<T, float> ||
        std::is_same_v<T, int> ||
        std::is_same_v<T, bool> ||
        std::is_same_v<T, char> ||
        std::is_same_v<T, double>
    ) {
        
        sequence[itemCount] = sizeof(T); 
        pkt.sequence[itemCount] = htons(sizeof(T)); 
    }
    
    else if constexpr (
        std::is_same_v<T, const char*> || std::is_same_v<T, char*>
    ) {
        sequence[itemCount] = strlen(value);
        pkt.sequence[itemCount] = htons(strlen(value));

    }
    else {
        throw std::runtime_error("Unknown type in pushSequence");
    }
}
#endif
