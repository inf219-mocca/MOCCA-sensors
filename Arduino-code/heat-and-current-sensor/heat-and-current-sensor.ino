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

EnergyMonitor emon1;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);

  emon1.current(1, 111.1);             // Current: input pin, calibration. 

  mlx.begin();  
}

void loop() {
  // Current sensor
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  double calcWatt = 0.0568 * Irms * 230.0;
  //TODO: Granulate
  if (calcWatt > 4) {
    Serial.print(calcWatt);
  } else {
    Serial.print(0);
  }

  // Heat sensor, split by a tab char so we can read it in Python
  Serial.print("\t");
  Serial.print(mlx.readObjectTempC()); 
  // End with a carriage return and newline, for proper newlines
  Serial.print("\r\n");
  
  delay(500);
}
