from serial import Serial

arduino_port = "/dev/ttyUSB1"
txt_file_path = "readings.txt"

ser = Serial(port, timeout=1000)

file = open(txt_file_path, "a")
while True:
    aReading = ser.readline(10)
    file.write(str(aReading, "utf-8"))
    file.flush()
