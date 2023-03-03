
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

#define SDCS 10
#define GPSTX 3
#define GPSRX 2

SoftwareSerial GPSSerial(GPSTX, GPSRX);
#define chipSelect 10
#define maxMsg 151

#define errorLED 5
#define standbyLED 6
#define workingLED 7

#define indLED 1


void setup() {
  // put your setup code here, to run once:
  
  if (indLED) {
    pinMode(errorLED, OUTPUT);
    pinMode(standbyLED, OUTPUT);
    pinMode(workingLED, OUTPUT);
  
    digitalWrite(errorLED, 0);
    digitalWrite(standbyLED, 1);
    digitalWrite(workingLED, 0);
  } 
  
  if (!SD.begin(chipSelect)) {
    // If SD card can't be initialized, blink error LED
    if (indLED) {
      while(1) {
        digitalWrite(errorLED, 1);
        delay(1000);
        digitalWrite(errorLED, 0);
        delay(1000);
      }
    }

    // otherwise just stall
    while (1);
  }

  GPSSerial.begin(9600);

  delay(5000);

  if (indLED) {
    digitalWrite(standbyLED, 0);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  static int loopCount = 0;
  File dataFile;
  char fname[] = "data2.txt";
  dataFile = SD.open(fname, FILE_WRITE);


  
  
  char gpsChar[151];

  if (loopCount < 10){
    int charCount = 0;
    while (GPSSerial.available() && charCount < 151) {
      gpsChar[charCount] = GPSSerial.read();
      charCount++;
    }
    gpsChar[charCount] = '\0';
    loopCount++;

    dataFile.println(gpsChar);
    dataFile.close();

    
    delay(1000);
  }
  
  else {
    if (indLED) {
      while(1) {
        digitalWrite(errorLED, 1);
        delay(200);
        digitalWrite(errorLED, 0);
        delay(200);
        digitalWrite(standbyLED, 1);
        delay(200);
        digitalWrite(standbyLED, 0);
        delay(200);
      }
    }
    while (1);
  }

  if (indLED) {
    digitalWrite(workingLED, 1);
    delay(200);
    digitalWrite(workingLED,0);
  }

}
