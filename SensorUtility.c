#include "SensorUtility.h"

uint8_t is_big_endian() {

    union {
        uint16_t i;
        char c[sizeof (uint16_t)];
    } endian = {0x1234};
    return endian.c[0] == 0x12;
}

int8_t swap(union sensor_packet* packet) {
    uint8_t size = sizeof (packet->value.value);
    uint8_t swapBuffer[size];
    memset(swapBuffer, 0, size);
    memcpy(swapBuffer, packet->bytes, size);
    size_t i;
    for (i = 0; i<sizeof (swapBuffer); i++) {
        packet->bytes[i] = swapBuffer[(size - 1) - i];
    }
    return 0;
}

int8_t write_sensor(void* data, uint8_t max_data_len, struct sensor_value* value, uint8_t* offset) {
    if (max_data_len >= (*offset + sizeof (union sensor_packet))) {
        uint8_t* buffer = (uint8_t*) data;
        union sensor_packet packet;
        packet.value = *value;

        if (!is_big_endian()) {
            swap(&packet);
        }

        uint8_t i;
        for (i = *offset; i < (sizeof (union sensor_packet) + *offset); i++) {
            buffer[i] = packet.bytes[i - *offset];
        }
        *offset += sizeof (union sensor_packet);
        return 0;
    }
    return EOVERFLOW;
}

int8_t read_sensor(void* data, uint8_t data_len, struct sensor_value* value, uint8_t* offset) {
    if (data_len >= (*offset + sizeof (union sensor_packet))) {
        uint8_t* buffer = (uint8_t*) data;
        union sensor_packet packet;

        uint8_t i;
        for (i = *offset; i < (sizeof (union sensor_packet) + *offset); i++) {
            packet.bytes[i - *offset] = buffer[i];
        }
        if (!is_big_endian()) {
            swap(&packet);
        }
        *value = packet.value;
        *offset += sizeof (union sensor_packet);
        return 0;
    }
    return EOVERFLOW;
}