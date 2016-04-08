# SensorUtility

This is a small library for someone who wants to send their float sensor values in compact size over uart/wireless/spi/i2c networks.

Using one structure and two functions you can trasfer your to systems with different endianness without care about swaping order.

# Structure

```struct sensor_value {
        float value;
        uint8_t type;
    }```

-		```float value``` value of your sensor
-		```uint8_t type``` sensor type (see header file)

# Functions

```int8_t write_sensor(void* data, uint8_t max_data_len, struct sensor_value* value, uint8_t* offset)``` is function for copying your sensor value into data buffer.

**Arguments:**
-		```void* data``` data buffer pointer for copying data into
-		```uint8_t max_data_len``` size of the buffer to prevent overflow
-		```struct sensor_value* value``` pointer to our sensor value structure to copy from
-		```uint8_t* offset``` pointer to offset uint where your data should start in buffer (offset is automatically increased by size of sensor_value)

**Return:**
-		```0``` if everything is alright
-		```EOVERFLOW``` if this operation could overflow data buffer

`int8_t read_sensor(void* data, uint8_t data_len, struct sensor_value* value, uint8_t* offset)` is function for copying your sensor value into data buffer.

**Arguments:**
-		```void* data``` data buffer pointer for copying data from
-		```uint8_t data_len``` size of the buffer to prevent overflow
-		```struct sensor_value* value``` pointer to our sensor value structure to copy to
-		```uint8_t* offset``` pointer to offset uint where your data should start in buffer (offset is automatically increased by size of sensor_value)

**Return:**
-		```0``` if everything is alright
-		```EOVERFLOW``` if this operation could overflow data buffer

