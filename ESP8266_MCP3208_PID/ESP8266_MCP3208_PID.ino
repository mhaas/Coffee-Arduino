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

const char *SSID = "Your SSID";
const char *PASSWORD = "Your Wifi Password";

const byte LED_PIN = 0;
const byte HEATER_RELAY_PIN = 1;
const byte SPI_CS_PIN = 16;

const byte HTTPD_PORT = 80;

const float ANALOG_REFERENCE = 3.3;

/* 
 *  Declare some global variables for the PID library.
 */

double desiredTemperature, currentTemperature, pidOutput;
double kP = 2;
double kI = 5;
double kD = 1;

/** Set the window size for the time proportioning control.
 *  See the original PID_Relayoutput example.
 *  
 *  The period of the signal is HEATER_WINDOW_SIZE ms (e.g. 5s) and
 *  the output of the PID is the duty cycle, e.g. how long the
 *  heater is one during that five second window.
 *  See: https://en.wikipedia.org/wiki/Duty_cycle
 *  
 *  This is similar to a slow version of PWM.
 */

const int HEATER_WINDOW_SIZE = 5000;


/**
 * This variable holds the timestamp of the last started window.
 * This will be updated after a window has elapsed and a new window starts.
 */
unsigned long windowStartTime;

/*
 * Initialize the PID library. Note that currentTemperate, pidOutput and desiredTemperature
 * are passed as pointers. Once we update the variables, the PID
 * library sees the changes automatically.
 */

PID heaterPID(&currentTemperature, &pidOutput, &desiredTemperature, kP, kI, kD, DIRECT);


/*
 * Initialize the temperature sensor library.
 * This is a version of the regular Seeed Studio HighTemp library modified to
 * use the MCP3208 ADC and a configurable analog reference voltage.
 */

HighTempMCP320x tempSensor(SPI_CS_PIN, 0, 1);

/**
 * Initialize webserver.
 */
ESP8266WebServer httpd( HTTPD_PORT);



// the setup function runs once when you press reset or power the board
void setup() {
  /* Initialize pins */
  pinMode(LED_PIN, OUTPUT);
  pinMode(HEATER_RELAY_PIN, OUTPUT);
  /* Reset pins */
  digitalWrite(LED_PIN, LOW);
  digitalWrite(HEATER_RELAY_PIN, LOW);

  /* Initialize Serial with 9600 baud because my USB<->Serial can't handle more */
  Serial.begin(9600);

  /* Some ADCs use 3.3.V, others use 5V as analog reference */
  tempSensor.setAnalogReference(ANALOG_REFERENCE);
  tempSensor.begin();

  /* Connect to WIFI */
  while ( WiFi.status() != WL_CONNECTED ) {
    // see https://github.com/sandeepmistry/esp8266-Arduino/blob/master/esp8266com/esp8266/libraries/ESP8266WiFi/src/include/wl_definitions.h
    // for valid status flags
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println( "" );
  Serial.print("Connected to ");
  Serial.println(SSID );
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /* Set up routing for the web server */

  httpd.on ( "/", handleRoot );
  httpd.onNotFound ( handleNotFound );
  httpd.begin();
  Serial.println ( "HTTP server started" );

  /* Initialize PID
   *  
   */

  // Set the period of the relay control signal
  heaterPID.SetOutputLimits(0, HEATER_WINDOW_SIZE);

  //turn the PID on

  // TODO: initialize the temperature sensor variables
  heaterPID.SetMode(AUTOMATIC);

}

// the loop function runs over and over again forever
void loop() {
  // Have to call getRoomTemp first..
  double roomTemperature = tempSensor.getRoomTmp();
  Serial.print("Room Temp:");
  Serial.println(roomTemperature);
  currentTemperature = tempSensor.getThmc();
  Serial.print("Temp: \n");
  Serial.print(currentTemperature);
  Serial.print("\n");

  // do PID stuff
  heaterPID.Compute();
  // TODO: what is the sample rate of the PID?
  // does it make sense to update the pidOutput more than once during a period?

  // How many milliseconds have passed since we have started the current window?
  float currentWindowElapsed = millis() - windowStartTime;
  
  if (currentWindowElapsed > HEATER_WINDOW_SIZE ) {
    //time to shift the Relay Window
    // TODO: just use current timestamp here?
    windowStartTime += HEATER_WINDOW_SIZE;
  }

  // Now decide if we are in the duty cycle of our period, i.e. if we want
  // to turn the relay for the header on or off
  if (pidOutput < currentWindowElapsed) {
    digitalWrite(HEATER_RELAY_PIN, HIGH);
  }
  else {
    digitalWrite(HEATER_RELAY_PIN, LOW);
  }
  
  
}

void handleRoot() {
  String message = "Hello World!";
  httpd.send ( 200, "text/plain", message );
}

void handleNotFound () {
  httpd.send(404, "text/plain", "Not found");
}


