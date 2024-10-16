#include <WiFi.h>

const char* ssid = "ESP32_Server";
const char* password = "tirtha2001";
WiFiServer server(8080);

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("Wi-Fi AP started");
  server.begin();
  Serial.println("Server started");
  Serial.print("Server IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\n');
        Serial.println("Received: " + message);
        client.println("Hello from ESP32 Server");
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
