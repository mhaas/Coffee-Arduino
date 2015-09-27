/* 
 *  Declare some global variables for the PID library.
 *
 */

const double DEFAULT_HEATER_KP = 2;
const double DEFAULT_HEATER_KI = 5;
const double DEFAULT_HEATER_KD = 1;

double desiredTemperature, currentTemperature, pidOutput;
double kP, kI, kD;

const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

/*
 * Initialize the PID library. Note that currentTemperate, pidOutput and desiredTemperature
 * are passed as pointers. Once we update the variables, the PID
 * library sees the changes automatically.
 */

PID* heaterPID;


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

const int HEATER_WINDOW_SIZE = 2000;


/**
 * This variable holds the timestamp of the last started window.
 * This will be updated after a window has elapsed and a new window starts.
 */
unsigned long windowStartTime;


void setupHeaterPID() {

  // HACK: init here to get kP, kI and kD in - these are are read from config after the first object
  // initialization
  heaterPID = new PID(&currentTemperature, &pidOutput, &desiredTemperature, kP, kI, kD, DIRECT);
  pinMode(HEATER_RELAY_PIN, OUTPUT);
  digitalWrite(HEATER_RELAY_PIN, RELAY_OFF);

#ifdef DBGLOG
  DEBUG.print("kP is:");
  DEBUG.println(kP);
  DEBUG.print("kI is:");
  DEBUG.println(kI);
  DEBUG.print("kD is:");
  DEBUG.println(kD);
#endif

  windowStartTime = millis();

  // Initialize PID

  // Set the period of the relay control signal
  heaterPID->SetOutputLimits(0, HEATER_WINDOW_SIZE);

  // turn the PID on
  // TODO: initialize the temperature sensor variables
  heaterPID->SetMode(AUTOMATIC);

}

void updateHeaterPID() {
  heaterPID->Compute();

  // TODO: what is the sample rate of the PID?
  // does it make sense to update the pidOutput more than once during a period?

  // How many milliseconds have passed since we have started the current window?
  float currentWindowElapsed = millis() - windowStartTime;

  if (currentWindowElapsed > HEATER_WINDOW_SIZE ) {
    //time to shift the Relay Window
    // TODO: just use current timestamp here?
    windowStartTime += HEATER_WINDOW_SIZE;
    DEBUG.print("Starting new window. PID says: ");
    DEBUG.println(pidOutput);
    DEBUG.print("Desired Temp:");
    DEBUG.println(desiredTemperature);
    
  }
  
  // Now decide if we are in the duty cycle of our period, i.e. if we want
  // to turn the relay for the header on or off
  if (currentWindowElapsed > pidOutput) {
    digitalWrite(HEATER_RELAY_PIN, RELAY_OFF);
  }
  else {
    digitalWrite(HEATER_RELAY_PIN, RELAY_ON);
  }


}


