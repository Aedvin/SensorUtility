#include <SensorUtility.h>

#define MAX_DATA_LEN 64 //arduino serial can hold 64 bytes

uint8_t buffer[MAX_DATA_LEN];

void setup() {
  Serial.begin(9600); //Setup UART 9600 baud
}

void loop() {
  if (Serial.available()) { //Any data new data

    uint8_t len = Serial.readBytes(buffer, MAX_DATA_LEN);  //read bytes into buffer and store amount of readed data

    if (len > 0) {

      struct sensor_value sensor;  //sensor structure
      uint8_t offset = 0;  //offset where our sensor data starts in buffer

      while (offset < len) {
        read_sensor(buffer, len, &sensor, &offset);  //read sensor data from buffer
        switch (sensor.type) {
          case SENSOR_TEMP:
            //we have temperature data in sensor
            break;
          case SENSOR_HUMIDITY:
            //we have humidity data in sensor
            break;
          case SENSOR_PRESSURE:
            //we have pressure data in sensor
            break;
          case SENSOR_VOLTAGE:
            //we have voltage data in sensor
            break;
        }
        float value =  sensor.value; //value of our sensor data
      }
    }
  }
  delay(50);
}
