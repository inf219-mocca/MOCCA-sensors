/***************************************************
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "EmonLib.h"
#include <cQueue.h>

EnergyMonitor emon1;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

typedef struct Readings {
  double current;
  double temp;
} Read;
Queue_t q;

void setup() {
  Serial.begin(9600);

  emon1.current(1, 111.1);             // Current: input pin, calibration.

  mlx.begin();

  // Create a new queue with size 10, allowing overwriting
  q_init(&q, 10, 10, LIFO, true);
}

void loop() {
  // Current sensor
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  double calcWatt = 0.0568 * Irms * 230.0;
  double temp = mlx.readObjectTempC();

  // Ignore noise from the reading
  if (calcWatt < 10) {
    calcWatt = 0;
  }

  // Create a new Readings struct and insert data
  Read read;
  read.current = calcWatt;
  read.temp = temp;
  // Push into the queue
  q_push(&q, &read);

  // Check if we have sent data over the serial interface
  if (Serial.available() > 0) {
    char incoming = Serial.read();

    // Check if it is 1
    if (incoming == '1') {
      Read read;
      q_pop(&q, &read);

      //TODO: Granulate
      Serial.print(read.current);
      // Heat sensor, split by a tab char so we can read it in Python
      Serial.print("\t");
      Serial.print(read.temp);
      // End with a carriage return and newline, for proper newlines
      Serial.print("\r\n");
    }
  }
}
