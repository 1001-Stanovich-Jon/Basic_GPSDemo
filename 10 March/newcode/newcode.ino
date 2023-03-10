
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <string.h>

#define SDCS 10
#define GPSTX 3
#define GPSRX 2

SoftwareSerial GPSSerial(GPSTX, GPSRX);
#define chipSelect 10
#define maxMsg 151

#define maxWrite 10

#define errorLED 5
#define standbyLED 6
#define workingLED 7

#define indLED 1

#define NMEALen 151

void blinkRunSuccess(void) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(workingLED, 1);
    delay(100);
    digitalWrite(workingLED,0);
  }
}


void blinkError(void) {
  digitalWrite(errorLED, 1);
  delay(1000);
  digitalWrite(errorLED, 0);
  delay(1000);
}

void blinkStall(void) {
  digitalWrite(errorLED, 1);
  delay(200);
  digitalWrite(errorLED, 0);
  delay(200);
  digitalWrite(standbyLED, 1);
  delay(200);
  digitalWrite(standbyLED, 0);
  delay(200);
}

bool isFix(char *p) {

  if (*p != '\0') {
    for (int i = 0; i < 6; i++) {
      p = strchr(p, ',') + 1;
    }
    char quality = *p;

    Serial.print("Your fix is: ");
    Serial.println(quality);

    if (quality == '1' || quality == '2' || quality == '3') {
      return 1;
    }

    else 
      return 0;
  }

  return 0;
}

void setup() {
  // put your setup code here, to run once:

  // Setup indicator LEDs
  if (indLED) {
    pinMode(errorLED, OUTPUT);
    pinMode(standbyLED, OUTPUT);
    pinMode(workingLED, OUTPUT);

  // Turn standby (green) LED on
    digitalWrite(errorLED, 0);
    digitalWrite(standbyLED, 1);
    digitalWrite(workingLED, 0);
  } 
  
  if (!SD.begin(chipSelect)) {
    // If SD card can't be initialized, blink error LED
    if (indLED)
      while(1) 
        blinkError();

    // If not using LEDs just stall
    while (1);
  }

  // Setup GPS UART at 9600 baud
  GPSSerial.begin(9600);

  // Start serial to computer
  Serial.begin(230400);

  // Delay to allow for GPS chip to start (not necessary)
  delay(5000);

  // Setup successful, can turn off standby light
  if (indLED) {
    digitalWrite(standbyLED, 0);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  // Loop controller for testing (so we don't keep writing forever)
  static int writeCount = 0;
  static int loopCount = 0;


  // Check write amount
  if (writeCount < 10 && loopCount < 20) {
    char incomingChar = '\0';
    char nextChar = '\0';

    
    if (GPSSerial.available()) {
      incomingChar = GPSSerial.read();
      while (incomingChar != '$') {
        if (GPSSerial.available()) {
        incomingChar = GPSSerial.read();
        }
      }

      
      incomingChar = GPSSerial.read();

      // Wait for enough bytes to arrive for checking
      while (GPSSerial.available() < 6) {};

      
      if (incomingChar == 'G') { incomingChar = GPSSerial.read();
        if (incomingChar == 'P') { incomingChar = GPSSerial.read();
          if (incomingChar == 'G') { incomingChar = GPSSerial.read();
            if (incomingChar == 'G') { incomingChar = GPSSerial.read();
              if (incomingChar == 'A') { 

                // We have identified GPGGA Sentence
                Serial.println("Detected GPGGA Sentence");
                
                

                // Setup storage for sentence
                char GPSData[NMEALen];
                memset(GPSData, 0, NMEALen);

                // now start reading and saving until newline
                int i = 0;
                nextChar = GPSSerial.read();

                while (nextChar != '\n' && nextChar != '$' && i < NMEALen - 1) {
                  
                  // Make sure there is data to read or you'll just read garbage
                  if (GPSSerial.available()) {
                    GPSData[i] = nextChar;
                    nextChar = GPSSerial.read();
                    i++;
                  }
                }

                // Terminate String
                GPSData[i] = '\0';

                Serial.print("Read data:");
                Serial.println(GPSData);
                Serial.println("-------");

                // Now we need to check if we've read valid data, otherwise it's worthless
                char *p = GPSData;
                if (isFix(p)) {
                  // We have a fix, write data
                  // Prepare file variable for uSD card, name it, open for write
                  File dataFile;
                  char fname[] = "data2.txt";
                  dataFile = SD.open(fname, FILE_WRITE);
                  Serial.println("We have a fix.");
                  Serial.println(GPSData);
                  dataFile.println(GPSData);
                  dataFile.close();
                  
                  writeCount++;
                  Serial.println("\n");
                }
    
                else {
                  // No fix, don't write
                  Serial.println("No fix");
                }
                loopCount++;
              }   
              loopCount++;
            }
          }
        }
      }
    }
  }
  
  else {
    // Written max times, just stall
    if (indLED) {
      while(1) {
        blinkStall();
      }

    }
    Serial.print("Why are we here?");

    // If not using LEDs
    while (1);
  }

  if (indLED) blinkRunSuccess();

}



// Use the god awful stuff below for parsing

#include <stdio.h>
#include <string.h>

int isFix(char *p) {

  
  if (*p != '\0') {
    for (int i = 0; i < 6; i++) {
      p = strchr(p, ',') + 1;
    }
    char quality = *p;

    printf("\n\nYou're fix is: %c\n\n", quality);
    
    if (quality >= '1' && quality <= '3') {
      return 1;
    }
  }
  return 0;
}

void getLat(char * p, char * latStorage) {
	for (int i = 0; i < 2; i++) {
		p = strchr(p, ',') + 1;
	}
	int i = 0;
	while (*p != ',') {
		latStorage[i] = *p;
		p++;
		i++;
	}
	p++;
	latStorage[i] = *p;
	latStorage[i+1] = '\0';
}

void getLon(char * p, char * lonStorage) {
	for (int i = 0; i < 4; i++) {
		p = strchr(p, ',') + 1;
	}
	int i = 0;
	while (*p != ',') {
		lonStorage[i] = *p;
		p++;
		i++;
	}
	p++;
	lonStorage[i] = *p;
	lonStorage[i+1] = '\0';
}

int main(void) {
	
	char *sentence = "$GPGGA,172814.000,3739.1933,N,12222.5638,W,1,04,2.5,81.5,M,-21.2,M,,*51";
	char *p = sentence;
	printf(p);
	
	char latitude[15];
	char longitude[15];
	
	if (isFix(p)) {
		printf("\nYou have a fix!");
		getLat(p, (char *) &latitude);
		printf("\nYour latitude is: %s", latitude);
		getLon(p, (char *) &longitude);
		printf("\nYour longitude is: %s", longitude);
	}
	
	else {
		printf("\nYou have no fix :(");
	}
	
	return 0;
}
