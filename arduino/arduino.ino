/*
Copyright (C) 2019  Eivind Dagsland Halderaker, Sondre Nilsen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
