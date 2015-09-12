/*
 * Initialize the temperature sensor library.
 * This is a version of the regular Seeed Studio HighTemp library modified to
 * use the MCP3208 ADC and a configurable analog reference voltage.
 */

HighTempMCP320x tempSensor(SPI_CS_PIN, 0, 1);



void setupTempSensor() {

  /* Some ADCs use 3.3.V, others use 5V as analog reference */
  tempSensor.setAnalogReference(ANALOG_REFERENCE);
  tempSensor.begin();

}

void updateTempSensor() {

  // Have to call getRoomTemp first..
  double roomTemperature = tempSensor.getRoomTmp();
  Serial.print("Room Temp:");
  Serial.println(roomTemperature);
  currentTemperature = tempSensor.getThmc() + offset;
  Serial.print("Temp: \n");
  Serial.print(currentTemperature);
  Serial.print("\n");



}

