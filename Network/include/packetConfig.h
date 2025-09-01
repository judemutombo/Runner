#include <cstddef>
#ifndef CONFIG_H
#define CONFIG_H

// Packet configuration
constexpr size_t MAX_MESSAGE_SIZE   = 128;
constexpr size_t MAX_TYPE_SEQ_SIZE  = 32;
constexpr size_t MAX_SEQ_SIZE       = 32;
constexpr size_t MAX_SENDER_ID_SIZE = 16;
constexpr size_t MAX_TYPE_SIZE      = 8;

constexpr uint16_t LIMIT_TYPE_SEQ = 10;
#endif
