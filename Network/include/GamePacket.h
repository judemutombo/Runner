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
#include "packet.h"

class GamePacket
{
public:
    GamePacket();
    GamePacket(const packet& p);
    ~GamePacket();
    void setSenderID(const char* senderId);
    void setMessageType(const char* messageType);
    packet getPacket();
    void setPaket(const packet& p);
    template<typename T> void push(const T& value);
    void push(const char* str);
    void push(const std::string& str);
    template<typename T> T pop();
    char* getSequence();
    char* getTypeSequence();
    
private:
    packet pkt;
    uint32_t floatToNet(float f);
    float netToFloat(uint32_t i);
    size_t offset = 0;
    char* sequence = nullptr;
    char* typeSequence = nullptr;
    template<typename T> void pushTypeSequence(const T& value);
    template<typename T> void pushSequence(const T& value);
    void popSequence();
    uint16_t limit = 11;
};
#endif

template<typename T> 
inline void GamePacket::push(const T& value){
    static_assert(std::is_arithmetic<T>::value, "Only arithmetic types are supported");

    if (offset + sizeof(T) > sizeof(pkt.messageData)) {
        throw std::overflow_error("Packet messageData overflow when pushing arithmetic : " + std::to_string(value));
    }

    size_t len = typeSequence ? strlen(typeSequence) : 0;
    if(len >= limit){
        throw std::overflow_error("typeSequence overflow when pushing arithmetic : " + std::to_string(value));
    }
    
    if constexpr (std::is_same<T, float>::value) {
        uint32_t net = floatToNet(value);
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
    pushSequence(value);
    pushTypeSequence(value);
}

template<typename T> 
inline T GamePacket::pop(){
    return 4;
}

template <typename T>
inline void GamePacket::pushTypeSequence(const T &value)
{
    size_t len = typeSequence ? strlen(typeSequence) : 0;

    // Allocate or reallocate to hold one more character + null terminator
    char* newSequence = (char*) realloc(typeSequence, sizeof(char) * (len + 2));
    if (!newSequence) {
        throw std::runtime_error("Memory allocation failed");
        return;
    }
    typeSequence = newSequence;

    if constexpr (std::is_same<T, int>::value){
        typeSequence[len] = 'I';
    }else if constexpr (std::is_same<T, float>::value){
        typeSequence[len] = 'F';
    }else if constexpr (std::is_same<T, double>::value){
        typeSequence[len] = 'D';
    }else if constexpr (std::is_same<T, bool>::value){
        typeSequence[len] = 'B';
    }else if constexpr (
        std::is_same<T, char*>::value ||
        std::is_same<T, const char*>::value ||
        std::is_same<T, char[]>::value ||
        std::is_same<T, const char[]>::value
    ){
        typeSequence[len] = 'S';
    }else if constexpr (std::is_same<T, char>::value){
        typeSequence[len] = 'C';
    }else{
        typeSequence[len] = '?'; 
    }

    typeSequence[len + 1] = '\0';
    memcpy(pkt.typesequence, typeSequence, 16);
    
}

template <typename T>
inline void GamePacket::pushSequence(const T& value) {
    size_t len = sequence ? strlen(sequence) : 0;
    char* newSequence;

    
    if constexpr (
        std::is_same_v<T, float> ||
        std::is_same_v<T, int> ||
        std::is_same_v<T, bool> ||
        std::is_same_v<T, char> ||
        std::is_same_v<T, double>
    ) {
        
        newSequence = (char*) realloc(sequence, len + 2);
        if (!newSequence) {
            throw std::runtime_error("Memory allocation failed");
        }
        sequence = newSequence;
        sequence[len] = std::to_string(sizeof(T)).c_str()[0]; 
        sequence[len + 1] = '\0';
    }
    
    else if constexpr (
        std::is_same_v<T, const char*> || std::is_same_v<T, char*>
    ) {
        size_t str_len = strlen(value);
        std::string marker = "," + std::to_string(str_len) + ","; 
        size_t marker_len = marker.length();

        newSequence = (char*) realloc(sequence, len + marker_len + 1);
        if (!newSequence) {
            throw std::runtime_error("Memory allocation failed");
        }
        sequence = newSequence;

        memcpy(sequence + len, marker.c_str(), marker_len);
        sequence[len + marker_len] = '\0';
    }
    else {
        throw std::runtime_error("Unknown type in pushSequence");
    }
}
