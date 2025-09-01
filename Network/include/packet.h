#include "packetConfig.h"

#pragma pack(push, 1)
typedef struct {
    uint16_t packetLength;         // Length of packet itself
    char messageType[MAX_TYPE_SIZE];        // E.g., "POS", "SPD", etc. (null-padded if shorter)
    char senderId[MAX_SENDER_ID_SIZE];          // Could be username, player ID, etc.
    uint8_t messageData[MAX_MESSAGE_SIZE];   // Actual data (can be anything)
    uint32_t messageOffset;
    uint16_t sequence[MAX_SEQ_SIZE];        
    char typeSequence[MAX_TYPE_SEQ_SIZE];
    uint16_t itemCount;
} packet;
#pragma pack(pop)