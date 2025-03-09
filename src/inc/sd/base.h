#ifndef SD_BASE
#define SD_BASE
#include <ArduinoJson.h>
#include <SD.h>

bool load_json_file(String path, JsonDocument &json);
bool save_json_file(String path, JsonDocument &json);
#endif