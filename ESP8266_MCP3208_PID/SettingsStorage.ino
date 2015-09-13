#include <EEPROM.h>

// Use EEPROM.put() and EEPROM.get() to write objects of any size, not just single bytes

// At which byte of the EEPROM the config data is stored
const size_t CONFIG_DATA_OFFSET = 32;

// The config version is checked to see if a (current) configuration
// is available.

// the length  of that config version string
const size_t CONFIG_VERSION_LENGTH = 4;


const char CONFIG_VERSION[CONFIG_VERSION_LENGTH] = "123";


// Code adapted from here: http://playground.arduino.cc/Code/EEPROMLoadAndSaveSettings

struct PidSettings {
  double desiredTemperature;
  double kP;
  double kI;
  double kD;
  double tempOffset;
  char configVersion[CONFIG_VERSION_LENGTH];
};


void setupSettings() {
  PidSettings config;
  // Read config from EEPROM
  EEPROM.get(CONFIG_DATA_OFFSET, config);
  if (strncmp(config.configVersion, CONFIG_VERSION, CONFIG_VERSION_LENGTH) != 0) {
    // no config found  - make one from default values
    config.desiredTemperature = DEFAULT_HEATER_TEMP;
    config.tempOffset = 0;
    config.kP = DEFAULT_HEATER_KP;
    config.kI = DEFAULT_HEATER_KI;
    config.kD = DEFAULT_HEATER_KD;
    // and write the config
    EEPROM.put(CONFIG_DATA_OFFSET, config);

    // TODO: commit() is not available on all Arduinos (?)
    EEPROM.commit();
  }

  // Load config from EEPROM
  EEPROM.get(CONFIG_DATA_OFFSET, config);
  // initialize global variables from config
  desiredTemperature = config.desiredTemperature;
  tempOffset = config.tempOffset;
  kP = config.kP;
  kI = config.kI;
  kD = config.kD;
}

void setKp(double _kp) {
  PidSettings config;
  EEPROM.get(CONFIG_DATA_OFFSET, config);
  config.kP = _kp;
  EEPROM.put(CONFIG_DATA_OFFSET, config);
  EEPROM.commit();
}

void setKi(double _ki) {
  PidSettings config;
  EEPROM.get(CONFIG_DATA_OFFSET, config);
  config.kI = _ki;
  EEPROM.put(CONFIG_DATA_OFFSET, config);
  EEPROM.commit();
}

void setKd(double _kd) {
  PidSettings config;
  EEPROM.get(CONFIG_DATA_OFFSET, config);
  config.kD = _kd;
  EEPROM.put(CONFIG_DATA_OFFSET, config);
  EEPROM.commit();
}

void setDesiredTemperature(double _temp) {
  PidSettings config;
  EEPROM.get(CONFIG_DATA_OFFSET, config);
  config.desiredTemperature = _temp;
  EEPROM.put(CONFIG_DATA_OFFSET, config);
  EEPROM.commit();
}

void setTempOffset(double _tempOffset) {
  PidSettings config;
  EEPROM.put(CONFIG_DATA_OFFSET, config);
  config.tempOffset = _tempOffset;
  EEPROM.put(CONFIG_DATA_OFFSET, config);
  EEPROM.commit();
}















