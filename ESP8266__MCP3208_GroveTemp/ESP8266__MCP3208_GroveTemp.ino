

#include <SPI.h>
#include <MCP3208.h>
#include <High_Temp_MCP320x.h>


const int CS_PIN = 16;
const float ANALOG_REFERENCE = 3.3;

HighTempMCP320x tempSensor(CS_PIN, 0, 1);



// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(0, OUTPUT);
  Serial.begin(9600);
  tempSensor.setAnalogReference(ANALOG_REFERENCE);
  tempSensor.begin();

}

// the loop function runs over and over again forever
void loop() {

  

  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  // Have to call getRoomTemp first..
  float roomtemp = tempSensor.getRoomTmp();
  Serial.print("Room Temp:");
  Serial.println(roomtemp);
  float temp = tempSensor.getThmc();
  Serial.print("Temp: \n");
  Serial.print(temp);
  Serial.print("\n");
  delay(100);
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}
