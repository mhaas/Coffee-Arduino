
/**
 * Initialize webserver.
 */
ESP8266WebServer httpd( HTTPD_PORT);

const char* DESIRED_TEMPERATURE_KEY = "desired_temp";


void setupHttpd () {
  /* Set up routing for the web server */
  httpd.on("/", handleRoot);
  httpd.on("/set", handleSet);
  httpd.onNotFound(handleNotFound);
  httpd.begin();
  DEBUG.println("HTTP server started");
}

// No need for a updateHttpd function, as the web server handles that itself
// outside the Arduino loop() function

void handleRoot() {
  String message = "Hello World!";
  httpd.send ( 200, "text/plain", message );
}

void handleNotFound () {
  httpd.send(404, "text/plain", "Not found");
}

void handleSet() {
  const char* value;

  // Iterate over all keys
  // TODO: handle remaining keys
  for (int i = 0; i < httpd.args(); i++) {

    // arg() normally returns a String object, but 
    // the character array (ironically) is easier to work with
    value = httpd.arg(i).c_str();
    
    if (strcmp(value, DESIRED_TEMPERATURE_KEY) == 0)  {
      // So, how do you use parseFloat?
      float tmp = atof(value);
      setDesiredTemperature(tmp);
      // TODO: when to update global variable?
      // Perhaps in SettingsStorage?
    } else {
      String error = "Invalid key: ";
      error += httpd.argName(i);
      httpd.send(500, "text/plain", error);
    }
  }
  httpd.send(200, "text/plain", "all set!");
}


