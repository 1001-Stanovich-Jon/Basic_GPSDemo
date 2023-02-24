
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

#define SDCS 10
#define GPSTX 3
#define GPSRX 2

SoftwareSerial GPSSerial(GPSTX, GPSRX);
const int chipSelect = 10;
const int maxMsg = 151;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  while(!Serial) {}
  if (!SD.begin(chipSelect)) {
    Serial.println("Can't use card...");
    while (1);
  }

  GPSSerial.begin(9600);

  Serial.println("Initialized.");
}

void loop() {
  // put your main code here, to run repeatedly:
  static int loopCount = 0;
  File dataFile;
  char fname[] = "data.txt";
  dataFile = SD.open(fname, FILE_WRITE);

  if (dataFile) {
    Serial.println("Opened file.");
  }
  
  
  char gpsChar[151];

  if (loopCount < 10){
    int charCount = 0;
    while (GPSSerial.available() && charCount < 151) {
      gpsChar[charCount] = GPSSerial.read();
      charCount++;
    }
    gpsChar[charCount] = '\0';
    loopCount++;
    Serial.println("Done with data cycle: ");
    Serial.println("Sentence below.");
    Serial.println(gpsChar);
    dataFile.println(gpsChar);
    dataFile.close();
    
    delay(1000);
  }
  else {
    Serial.println("This is the end.");
    while (1);
  }

}
