void setupWifi() {
  DEBUG.println("Connecting to WIFI!");
  WiFi.begin(SSID, PASSWORD);
  
  /* Connect to WIFI */
  while (WiFi.status() != WL_CONNECTED) {
    // see https://github.com/sandeepmistry/esp8266-Arduino/blob/master/esp8266com/esp8266/libraries/ESP8266WiFi/src/include/wl_definitions.h
    // for valid status flags
    delay(500);
    DEBUG.print(".");
  }
  DEBUG.println("");
  DEBUG.print("Connected to ");
  DEBUG.println(SSID );
  DEBUG.print("IP address: ");
  DEBUG.println(WiFi.localIP());
}

void updateWifi() {
  // No-op right now
  // TODO: check Wifi connectivity status - unless ESP8266 reconnects automatically?
}


