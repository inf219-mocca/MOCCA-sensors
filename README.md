# MOCCA-sensors

## What
This repository contains the source code of what the Arduino is running: reading
temperature and power from the coffee machine and serving it over the wire to
whomever listens.

## Dependencies
This project has a few dependencies that you are required to install to be able
to compile your code, these can all be downloaded through the built-in library
downloader in the Arduino IDE.

- [`cQueu`](https://github.com/SMFSW/cQueue)
- [`EmonLib`](https://github.com/openenergymonitor/EmonLib)
- [`Adafruit-MLX90614`](https://github.com/adafruit/Adafruit-MLX90614-Library)

## Usage
This code has only been tested on an Arduino Uno, so no guarantees for any other
kind of board. To use it simply open the `arduino.ino` file in the Arduino IDE,
configure it to read/write to the correct USB port and compile and push it.

If you want to read data you need to open the TTY display and send a `1` which
the Arduino will receive and return the latest reading from its sensors.
Anything else is simply ignored.
