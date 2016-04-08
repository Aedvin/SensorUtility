/*
 * File:   SensorUtility.h
 * Author: Alda
 *
 * Created on 11. března 2016, 21:28
 */


#ifndef SENSORUTILITY_H
#define	SENSORUTILITY_H

#include <stdint.h>
#include <string.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define SENSOR_TEMP 0x00
#define SENSOR_HUMIDITY 0x01
#define SENSOR_PRESSURE 0x02
#define SENSOR_VOLTAGE 0x03

#define EOVERFLOW -1;

    struct sensor_value {
        float value;
        uint8_t type;
    } __attribute__((__packed__));

    union sensor_packet {
        struct sensor_value value;
        uint8_t bytes[sizeof (struct sensor_value)];
    };

    int8_t swap(union sensor_packet* packet);

    int8_t write_sensor(void* data, uint8_t max_data_len, struct sensor_value* value, uint8_t* offset);

    int8_t read_sensor(void* data, uint8_t data_len, struct sensor_value* value, uint8_t* offset);

    uint8_t is_big_endian();


#ifdef	__cplusplus
}
#endif

#endif	/* SENSORUTILITY_H */

