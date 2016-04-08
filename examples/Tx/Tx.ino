#include <SPI.h>
#include <SensorUtility.h>


#define MAX_DATA_LEN 64 //arduino serial can hold 64 bytes

uint8_t buffer[MAX_DATA_LEN];
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  if (millis() - lastMillis > 5000) { //after 5 seconds from last transmit send new data

    struct sensor_value temperature;  //We will create three example sensors
    temperature.type = SENSOR_TEMP;  //temperature sensor

    struct sensor_value humidity;
    humidity.type = SENSOR_HUMIDITY;  //humidity sensor

    struct sensor_value pressure;
    pressure.type = SENSOR_PRESSURE;  //pressure sensor

    temperature.value = 24.6f;  //init their values
    humidity.value = 78.5f;
    pressure.value = 789.3f;

    uint8_t offset = 0;
    write_sensor(buffer, MAX_DATA_LEN, &temperature, &offset); //write temperature sensor into data buffer
    write_sensor(buffer, MAX_DATA_LEN, &humidity, &offset); // same with humidity
    write_sensor(buffer, MAX_DATA_LEN, &pressure, &offset); //same with pressure

    Serial.write(buffer, offset); //and finally send it to other side
    lastMillis = millis();
  }
}
