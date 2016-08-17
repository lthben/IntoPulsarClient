void init_wifi() {
  Serial.println();
  Serial.println();

  Serial.println();
  Serial.println();
  Serial.print("Connecting to");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  udp.beginMulticast(WiFi.localIP(), ipMulti, portMulti);
  Serial.println("UDP established");
}

void listen_for_udp_packet() { //gets the analog value of the motor speed between 300 to 600
  int numBytes = udp.parsePacket();

  if (!numBytes) {
    //do nothing
  } else {
    udp.read( (unsigned char *) &motorSpeedVal, sizeof(motorSpeedVal));
    //    Serial.println(motorSpeedVal);
  }
}

unsigned long request_pov_pixels(IPAddress& address, float angle)
{ //for the RasPi webcam
  udp.beginPacket(address, SERVER_PORT);
  udp.write((char *) &angle, sizeof(angle));
  udp.endPacket();
}


