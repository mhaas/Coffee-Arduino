#ifndef TEMP_SENSOR_H

#define TEMP_SENSOR_H

/*
 * Initialize the temperature sensor library.
 * This uses a version of the regular Seeed Studio HighTemp library modified to
 * use the MCP3208 ADC and a configurable analog reference voltage.
 */

#include <High_Temp_MCP320x.h>

#include "SettingsStorage.h"

//#include <../Grove_HighTemp_Sensor/High_Temp_MCP320x.h>



class TempSensor {

  public:
    TempSensor(SettingsStorage* _settings);
    //~TempSensor();
    void begin(const byte _spiCsPin, const double _analogReference);
    void update();

  private:
    HighTempMCP320x* sensor;
    SettingsStorage* settings;
    int lastRead;
    const int TEMP_INTERVALL = 500;
    
};

#endif
