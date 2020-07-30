#pragma once

// Uncomment for quick debugging of communication with the device
//#define ENABLE_NEXTION_LOGGER

#ifdef ENABLE_NEXTION_LOGGER
#define NextionLog(args...) Serial.printf(args)
#define NextionLogBin(buffer, start, length)          \
    {                                                 \
        for (uint16_t i = 0; i < length; ++i)         \
        {                                             \
            if (buffer[start + i] < 16)               \
            {                                         \
                Serial.print('0');                    \
            }                                         \
            Serial.print((int)buffer[start + i], 16); \
            Serial.print(' ');                        \
        }                                             \
        Serial.println();                             \
    }
#define NextionLogArray(buffer, start, length) \
    {                                          \
        for (uint16_t i = 0; i < length; ++i)  \
        {                                      \
            Serial.print(buffer[start + i]);   \
            Serial.print(' ');                 \
        }                                      \
        Serial.println();                      \
    }
#define NextionLogStr(buffer, start, length)       \
    {                                              \
        for (uint16_t i = 0; i < length; ++i)      \
        {                                          \
            Serial.print((char)buffer[start + i]); \
        }                                          \
        Serial.println();                          \
    }
#else
#define NextionLog(args...)
#define NextionLogBin(buffer, start, length)
#define NextionLogArray(buffer, start, length)
#define NextionLogStr(buffer, start, length)
#endif
