/*
ENGG4802

Jesse Claven
Supervisor: Mark Schulz
*/

#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h> 
#include <Ethernet.h>

#include <Base64.h>
#include <global.h>
#include <MD5.h>
#include <sha1.h>
#include <WebSocketClient.h>

#include <ArduinoJson.h>

#include <DDP.h>

/*******************************************************************************
* ETHERNET
*******************************************************************************/
// 90:a2:da:00:00:17
// EEPROM locations
const int eepromMacFlag = 0; // 1 byte
const int eepromMacAddress = 1; // 3 bytes

// Default MAC address for the ethernet controller.
// Unique MAC address can be stored in EEPROM using Set_MAC_Address sketch
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0xFF, 0xFF};

const int outputStringLen = 200;
char outputString[outputStringLen];  // buffer used for constructing output strings

/*******************************************************************************
* RGB colour sensor
*******************************************************************************/
/*
An Arduino code example for interfacing with the 
HDJD-S822-QR999 Color Sensor.  Put an object in front of the
sensor and look at the serial monitor to see the values the sensor
is reading.  Scaling factors and gains may have to be adjusted
for your application.

by: Jordan McConnell
 SparkFun Electronics
 created on: 1/24/12
 license: OSHW 1.0, http://freedomdefined.org/OSHW
 
Connect the gain pins of the sensor to digital pins 7 - 12 (or ground).
Connect the led pin to digital 13.
Connect Vr to analog 0, Vg to analog 1, and Vb to analog 2.
*/
const int ledpin = 32;
// 7 - 12 pwm (digital)
const int GSR1 = 30;
const int GSR0 = 33;
const int GSG1 = 34;
const int GSG0 = 36;
const int GSB1 = 46;
const int GSB0 = 48;

const int Vr = A3;
const int Vg = A4;
const int Vb = A5;

// Sensor read values
int r = 0;
int g = 0;
int b = 0;

/*******************************************************************************
* RGB LED
*******************************************************************************/
const int LEDr = 26;
const int LEDg = 22;
const int LEDb = 24;

int rVal = 0;
int gVal = 0;
int bVal = 0;

/*******************************************************************************
* DDP
*******************************************************************************/
DDP ddp = DDP();

/******************************************************************************/
void setup() {
  Serial.begin(9600);

  setupEthernet();
  //setupColourSensor();
  //setupRGBLED();
  ddp.setup("www.google.com");
}

void loop() {
  //readColour();
  //printColour();
  //fadeColour();
}

/*******************************************************************************
* ETHERNET
*******************************************************************************/
void setupEthernet() {
  // start the Ethernet connection and the server:
  // Retrieve MAC address from EEPROM if present
  if (EEPROM.read(eepromMacFlag) == '#') {
    Serial.println("Retrieving MAC address from EEPROM");
    for (int i = 0; i < 3; i++) {
      mac[i+3] = EEPROM.read(eepromMacAddress + i);
    }
  } 
  else {
    Serial.println("No MAC address stored in EEPROM");
    Serial.println("Using default MAC address");
  }  

  snprintf(outputString, outputStringLen, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  Serial.print("MAC Address: ");
  Serial.println(outputString);

  Serial.println("DHCP...");

  while (Ethernet.begin(mac) == 0) {
    Serial.println("No DHCP");
    delay(500);
    Serial.println("DHCP...");
  }
  Serial.println("IP address: ");
  Serial.println(Ethernet.localIP());
}

/*******************************************************************************
* RGB colour sensor
*******************************************************************************/
/* */
void setupColourSensor() {
  // Set PIN modes
  pinMode(ledpin, OUTPUT);
  pinMode(GSR1, OUTPUT);
  pinMode(GSR0, OUTPUT);
  pinMode(GSG1, OUTPUT);
  pinMode(GSG0, OUTPUT);
  pinMode(GSB1, OUTPUT);
  pinMode(GSB0, OUTPUT);

  // Turn on the LED
  onColourSensorLED();
  
  // Set the gain of each sensor
  digitalWrite(GSR1, LOW);
  digitalWrite(GSR0, LOW);
  digitalWrite(GSG1, LOW);
  digitalWrite(GSG0, LOW);
  digitalWrite(GSB1, LOW);
  digitalWrite(GSB0, LOW);
}

/* Read sensors */
void readColour() {
  // On page 7 of the datasheet, there is a graph of the 
  // spectral responsivity of the chip.  Scaling factors were
  // selected based on this graph so that the gain of each 
  // color is closer to being equal
  r = analogRead(Vr) * 10;
  g = analogRead(Vg) * 14;
  b = analogRead(Vb) * 17;
}

/* (DEBUG)  Print values to the serial monitor*/
void printColour() {
  Serial.print("Red: ");
  Serial.print(r, DEC);
  Serial.print("\t\tGreen: ");
  Serial.print(g, DEC);
  Serial.print("\t\tBlue: ");
  Serial.print(b, DEC);
  Serial.println();
}

void offColourSensorLED() {
  digitalWrite(ledpin, LOW);
}

void onColourSensorLED() {
  digitalWrite(ledpin, HIGH);
}

/*******************************************************************************
* RGB LED
*******************************************************************************/
/* */
void setupRGBLED() {
	pinMode(LEDr, OUTPUT);
	pinMode(LEDg, OUTPUT);
	pinMode(LEDb, OUTPUT);

	setColour(rVal, gVal, bVal);
}

void setColour(int valR, int valG, int valB) {
  // Red
  rVal = valR;
  analogWrite(LEDr, rVal);
  // Green
  gVal = valG;
  analogWrite(LEDg, gVal);
  // Blue
  bVal = valB;
  analogWrite(LEDb, bVal);
}

/* (DEBUG) */
void fadeColour() {
  for (int i = 0; i < 255; i++) {
    setColour(i, 255 - i, 0);
    delay(50);
  }
  for (int i = 0; i < 255; i++) {
    setColour(255 - i, i, 0);
    delay(50);
  }
}
