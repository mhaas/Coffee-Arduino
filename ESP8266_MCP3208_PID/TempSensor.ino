/*
 * Initialize the temperature sensor library.
 * This uses a version of the regular Seeed Studio HighTemp library modified to
 * use the MCP3208 ADC and a configurable analog reference voltage.
 */

HighTempMCP320x tempSensor(SPI_CS_PIN, 0, 1);


int lastRead = 0;
const int TEMP_INTERVALL = 500;

void setupTempSensor() {

  /* Some ADCs use 3.3.V, others use 5V as analog reference */
  tempSensor.setAnalogReference(ANALOG_REFERENCE);
  tempSensor.begin();

}

void updateTempSensor() {

  // Sample every TEMP_INTERVALL ms
  int now = millis();
  if (now > lastRead + TEMP_INTERVALL) {
    lastRead = now;
    // Have to call getRoomTmp first..
    double roomtmp = tempSensor.getRoomTmp();
    currentTemperature = tempSensor.getThmc() + tempOffset;
#ifdef DBGLOG
    DEBUG.print("Current Temperature: ");
    DEBUG.println(currentTemperature);
    DEBUG.print("Current roomTemp: ");
    DEBUG.println(roomtmp);
#endif
  }
  
}


