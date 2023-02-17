// This file is frankensteined together, still needs editing

// For OLED we'll use Adafruit's built in library (we can look at this later if you want)
//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // Library lists address as 0x3D but that's not correct
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // SEt screen height, address, and reset

#include <Wire.h>  // For I2C Comms

#define GPSTX 3 // GPS Board's TX (RX on Arduino)
#define GPSRX 2 // GPS Board's RX (TX on Arduino)

// Need for GPS so we don't have UART clash on hardware Serial
#include <SoftwareSerial.h>

SoftwareSerial GPSSerial(GPSTX, GPSRX); // First argument is pin to RECEIVE data on, second is to SEND data on

// include the SD library:
//#include <SPI.h>
//#include <SD.h>


//File myFile;

void setup() {

  GPSSerial.begin(9600);
  Serial.begin(115200);
  while (!Serial) {} //
  Wire.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1) {}; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  //Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  /*if (SD.begin(chipSelect)) {
    Serial.println("initialization failed.");
    while (1);
  } else {
    Serial.println("Card initialized.");
  }*/


  // re-open the file for reading (don't need to specify fo reading):
  /*myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file to end
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close  file:
    myFile.close();
  } else {
    Serial.println("error opening file");
  }*/
}

void loop() {
  delay(1000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  int maxMessage = 150;
  char GPSData[maxMessage + 1];
  int charCount = 0;
  while (GPSSerial.available() > 0 && charCount < maxMessage) {
    GPSData[charCount] = GPSSerial.read();
    charCount++;
  }
  GPSData[charCount] = '\0';


  display.println(F("Some GPS Data Below"));
  for (int i = 0; i < 18; i++) {
    display.print(GPSData[i]);
  }
  display.display();
  delay(1000);
  /*
  // Open SD Card and write some data to it
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("GPSTest.txt", FILE_WRITE);

  // if the file opened okay, write
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println(GPSData);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }


  // re-open the file for reading (don't need to specify fo reading):
  myFile = SD.open("GPSTest.txt");
  if (myFile) {
    Serial.println("GPSTest.txt Opened:");

    // read from the file to end
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close  file:
    myFile.close();
  } else {
    Serial.println("error opening file");
  }
  */
  
}
