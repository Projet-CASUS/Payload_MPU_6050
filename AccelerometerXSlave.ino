#include "Adafruit_MPU6050.h"
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "Timer.h"

const int chipSelect = 53;
Sd2Card card;
SdVolume volume;
SdFile root;
String message = "";
Adafruit_MPU6050 mpu;
File dataFile;
unsigned long MS;
unsigned long start;
void setup(void) {
  pinMode(4,INPUT);
  delay(5000);
  if (!mpu.begin()) {

    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    while (1);
  }
  //Serial.println("card initialized.");
  SPI.begin();
  Wire.begin();
  Wire.setClock(3400000);
  bool condition = true;
  while(condition)
  {
    Serial.print(digitalRead(4));
     if(digitalRead(4) == HIGH)
     {
         start=millis();
         condition = false;
     }
  }
}
 

void loop() {

      sensors_event_t a;
      mpu.getAccel(&a);
      MS = millis()-start;
      message = message + MS + "," + a.acceleration.x+ '\n';
      if(message.length() > 500)
      {
        dataFile = SD.open("datalog.txt", FILE_WRITE);
        dataFile.print(message);
        dataFile.close();
        message = "";
     }
}
