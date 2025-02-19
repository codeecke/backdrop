#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <Arduino.h>
#include "./WebSocketCommand.h"

class JSONParser
{
private:
    /* data */
public:
    WebSocketCommand parseWebSocketCommand(String json);
};

#endif
