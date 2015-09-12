
/**
 * Initialize webserver.
 */
ESP8266WebServer httpd( HTTPD_PORT);


void setupHttpd () {
  /* Set up routing for the web server */
  httpd.on ( "/", handleRoot );
  httpd.onNotFound ( handleNotFound );
  httpd.begin();
  DEBUG.println ( "HTTP server started" );
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

