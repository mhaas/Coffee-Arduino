#include <EEPROM.h>

// Use EEPROM.put() and EEPROM.get() to write objects of any size, not just single bytes



// Compute the indices for the values stored in the EEPROM
// Each value is stacked on the previous one
const size_t HEATER_PID_KP_IDX = 0;
const size_t HEATER_PID_KI_IDX = HEATER_PID_KP_IDX + sizeof(kP);
const size_t HEATER_PID_KD_IDX = HEATER_PID_KI_IDX + sizeof(kI);
const size_t HEATER_DESIRED_TEMP = HEATER_PID_KD_IDX + sizeof(desiredTemperature);
const size_t TEMP_SENSOR_OFFSET = HEATER_DESIRED_TEMP + sizeof(offset);












