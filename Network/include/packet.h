#pragma pack(push, 1)
typedef struct {
    uint8_t dataLength;         // Length of packet itself
    char messageType[8];        // E.g., "POS", "SPD", etc. (null-padded if shorter)
    char senderId[16];          // Could be username, player ID, etc.
    uint8_t messageData[128];   // Actual data (can be anything)
    char sequence[128];
    char typesequence[11];
} packet;
#pragma pack(pop)