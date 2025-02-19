#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <variant>
#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "./wificonnection.h"
#include "./inc/Motor.h"
#include "./WebServer.h"
#include "./inc/commands/StopCommand.h"
#include "./inc/commands/MoveCommand.h"
#include "./inc/commands/CalibrateCommand.h"
#include "./inc/CommandRegistry.h"
#include "./inc/PersistentMotorPositions.h"
#include "./inc/events/MotorRunningEvent.h"
#include "./inc/events/PositionUpdateEvent.h"
#include "./Webserver.h"

#include "freertos/queue.h"

QueueHandle_t eventQueue;

u_long lastDebug = 0;
Motor *motors[2] = {&motor1, &motor2};
PersistentMotorPositions persistentMotorPositions(motors);

void runningEventListener(void *payload)
{
  if (!payload)
  {
    Serial.println("Error: Payload is null!");
    return;
  }

  MotorRunnningEventPayload *data = static_cast<MotorRunnningEventPayload *>(payload);
  Serial.printf("Motor %d started. Direction %s / Speed: %f\r\n", data->motorId, data->direction, data->speed);
  MotorRunningEventPayload payloadData;
  payloadData.direction = data->direction;
  payloadData.running = data->speed != 0;

  MotorRunningEvent event(data->motorId, payloadData);
  event.send(&ws);
}

void positionUpdateEventTask(void *payload)
{
  if (!payload)
  {
    Serial.println("Error: Payload is null!");
    vTaskDelete(NULL);
    return;
  }

  PositionUpdateEventPayload *data = static_cast<PositionUpdateEventPayload *>(payload);
  PositionUpdateEvent event(data->motorId, data->position);

  Serial.printf("Sende PositionUpdateEvent für Motor %d, Position %d\n", data->motorId, data->position);
  event.send(&ws);
  Serial.println("positionUpdateEvent gesendet");

  delete data; // Speicher freigeben
  vTaskDelete(NULL);
}

void positionUpdateEvent(void *payload)
{
  if (!payload)
  {
    Serial.println("Error: Payload is null!");
    return;
  }

  // Event-Daten sicher auf den Heap kopieren
  PositionUpdateEventPayload *heapData = new PositionUpdateEventPayload(*(PositionUpdateEventPayload *)payload);

  // Neuen FreeRTOS-Task für das Senden erstellen
  if (xTaskCreate(
          positionUpdateEventTask, // Task-Funktion
          "sendPositionUpdateEvent",
          4096,     // Stack-Größe
          heapData, // Parameter (Heap-Daten)
          1,        // Priorität
          NULL) != pdPASS)
  {
    Serial.println("Fehler: Konnte Task nicht starten!");
    delete heapData; // Falls Task-Erstellung fehlschlägt, Speicher freigeben
  }
}

void setup(void)
{

  eventQueue = xQueueCreate(10, sizeof(PositionUpdateEventPayload));

  motor1.addEventListener("started", runningEventListener);
  motor2.addEventListener("started", runningEventListener);

  motor1.addEventListener("stopped", runningEventListener);
  motor2.addEventListener("stopped", runningEventListener);

  motor1.addEventListener("positionUpdate", positionUpdateEvent);
  motor2.addEventListener("positionUpdate", positionUpdateEvent);

  StopCommand *stopCommandMotor1 = new StopCommand(&motor1);
  MoveCommand *moveCommandMotor1 = new MoveCommand(&motor1);
  CalibrateCommand *calibrateCommandMotor1 = new CalibrateCommand(&motor1);

  StopCommand *stopCommandMotor2 = new StopCommand(&motor2);
  MoveCommand *moveCommandMotor2 = new MoveCommand(&motor2);
  CalibrateCommand *calibrateCommandMotor2 = new CalibrateCommand(&motor2);

  commandRegistry.registerCommand(stopCommandMotor1);
  commandRegistry.registerCommand(moveCommandMotor1);
  commandRegistry.registerCommand(calibrateCommandMotor1);
  commandRegistry.registerCommand(stopCommandMotor2);
  commandRegistry.registerCommand(moveCommandMotor2);
  commandRegistry.registerCommand(calibrateCommandMotor2);

  Serial.begin(115200);
  // esp_log_level_set("*", ESP_LOG_VERBOSE); // Zeigt alle Logs an
  // esp_reset_reason_t reason = esp_reset_reason();
  // Serial.printf("Reset Reason: %d\n", reason);

  // fsSetup();
  wifiSetup();
  // Wait for connection

  ws_setup();

  // setupServer();
  //  ArduinoOTA.setHostname("backdrop");
  //  ArduinoOTA.setPassword("password");
  //  ArduinoOTA.begin();
}

void loop()
{
  motor1.run();
  motor2.run();
  ws_loop();
}