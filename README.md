# MOCCA-sensors

## Getting readings from the Arduino

### Setup getReadings.py
Make sure you have `pipenv` installed and the run `pipenv sync --dev`. 
Edit [getReadings.py](Readings/getReadings.py) with correct arduino_port and file path for the sensor data: 
```python
arduino_port = "/dev/<port>"
txt_file_path = "<filepath>.txt"
``` 
Now you are ready to start reading! Run [getReadings.py](Readings/getReadings.py) by running `pipenv run python getReadings.py`. The file should now be filled up with sensor data.

## Readings
[readings.txt](Readings/readings.txt) contains sensor data from a Moccamaster brewing and warming the pot.
