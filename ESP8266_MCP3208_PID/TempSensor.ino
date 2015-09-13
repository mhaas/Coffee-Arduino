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

  // TODO: add a check to only sample every X ms, no-nop otherwise
  
  // Have to call getRoomTemp first..
  tempSensor.getRoomTmp();
  currentTemperature = tempSensor.getThmc() + tempOffset;
}

