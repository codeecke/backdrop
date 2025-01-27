#include <Arduino.h>
#include "./wificonnection.h"
// #include <ArduinoOTA.h>
#include <./Motor.h>
#include "esp_log.h"
#include "./WebServer.h"

/*
| Pin-Nummer | Funktion     |
| ---------- | ------------ |
| 34         | Sensor Pin 1 |
| 35         | Sensor Pin 2 |
| 32         | Button       |
| 33         | Relais 1     |
| 25         | Relais 2     |
*/

void setup(void)
{
  Serial.begin(115200);
  esp_log_level_set("*", ESP_LOG_VERBOSE); // Zeigt alle Logs an
  esp_reset_reason_t reason = esp_reset_reason();
  Serial.printf("Reset Reason: %d\n", reason);
  motor1.setup();

  // fsSetup();
  wifiSetup();
  // Wait for connection

  ws_setup();

  // setupServer();
  // ArduinoOTA.setHostname("backdrop");
  // ArduinoOTA.setPassword("password");
  // ArduinoOTA.begin();
}

void loop()
{
  motor1.loop();
  ws_loop();

  if (Serial.available() > 0) // Prüfen, ob Daten verfügbar sind
  {
    char c = Serial.read();
    Serial.printf("Eingabe: %d\n", c);
    switch (c)
    {
    case 65:
      Serial.println("hoch");
      motor1.up();
      break;
    case 66:
      Serial.println("runter");
      motor1.down();
      break;
    case 67:
    case 68:
      Serial.println("stop");
      motor1.stop();
    }
  }
  esp_task_wdt_reset();
  delay(10);
}