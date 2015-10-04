#include "HeaterPID.h"


HeaterPID::HeaterPID(SettingsStorage* _settings, Stream* _dbgStream) {
  settings = _settings;
  dbgStream = _dbgStream;
}

void HeaterPID::begin(const int _relayPin) {
  relayPin = _relayPin;

  pid = new PID(settings->getCurrentTemperature(), &pidOutput, settings->getDesiredTemperature(), settings->getKp(),
                      settings->getKi(), settings->getKd(), DIRECT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, RELAY_OFF);

  windowStartTime = millis();

  // Initialize PID

  // Set the period of the relay control signal
  pid->SetOutputLimits(0, HEATER_WINDOW_SIZE);

  // turn the PID on
  // TODO: initialize the temperature sensor variables
  pid->SetMode(AUTOMATIC);

}

void HeaterPID::update() {
  pid->Compute();

  // TODO: what is the sample rate of the PID?
  // does it make sense to update the pidOutput more than once during a period?

  // How many milliseconds have passed since we have started the current window?
  float currentWindowElapsed = millis() - windowStartTime;

  if (currentWindowElapsed > HEATER_WINDOW_SIZE ) {
    //time to shift the Relay Window
    // TODO: just use current timestamp here?
    windowStartTime += HEATER_WINDOW_SIZE;
    dbgStream->print("Starting new window. PID says: ");
    dbgStream->println(pidOutput);
    dbgStream->print("Desired Temp:");
    dbgStream->println(*(settings->getDesiredTemperature()));

  }

  // Now decide if we are in the duty cycle of our period, i.e. if we want
  // to turn the relay for the header on or off
  if (currentWindowElapsed > pidOutput) {
    digitalWrite(relayPin, RELAY_OFF);
  }
  else {
    digitalWrite(relayPin, RELAY_ON);
  }


}


