

#include <SPI.h>
#include <MCP3208.h>

int CS_PIN = 16;

MCP3208 adc(CS_PIN);


// the setup function runs once when you press reset or power the board
void setup() {
  adc.begin();
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  char temp[10];
  
  Serial.print("ADC 0:\n");
  sprintf(temp, "%5d", adc.analogRead(0));
  Serial.print(temp);
  Serial.print("\n");
  Serial.print("ADC 1:\n");
  sprintf(temp, "%5d", adc.analogRead(1));
  Serial.print(temp);
  Serial.print("\n");
  delay(1000);
}
