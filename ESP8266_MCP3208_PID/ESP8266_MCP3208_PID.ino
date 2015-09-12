

/**
 * 
 * Initial sketch for a PID-controlled heater
 * Untested!
 */

#include <SPI.h>
#include <MCP3208.h>
#include <High_Temp_MCP320x.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// http://playground.arduino.cc/Code/PIDLibrary
#include <PID_v1.h>

#define DEBUG Serial

/**
 * Some configuration constants
 */
const char *SSID = "Your SSID";
const char *PASSWORD = "Your Wifi Password";
const byte LED_PIN = 0;
const byte HEATER_RELAY_PIN = 1;
const byte SPI_CS_PIN = 16;
const byte HTTPD_PORT = 80;
const float ANALOG_REFERENCE = 3.3;
/**  
 * Default desired heater temperature if no
 * value is set in the EEPROM
 */
const byte DEFAULT_HEATER_TEMP = 85;

/**
 * End configuration constants
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize Serial with 9600 baud because my USB<->Serial can't handle more
  DEBUG.begin(9600);

  // Initialize and reset pins
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  setupHeaterPID();
  setupHttpd();
  setupTempSensor();
  setupWifi();
}

// the loop function runs over and over again forever
void loop() {
  // TODO: don't update tempsensor too often,
  // or the ADC will return bogus values
  updateTempSensor();
  updateHeaterPID();
  updateWifi();
}


