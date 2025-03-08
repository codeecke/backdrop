#include "./WebServer.h"

AsyncWebServer server(80);

void handlePublicFiles(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "Hello World");
}

void webserver_setup(AsyncWebSocket *ws)
{
    if (ws != nullptr)
    {
        server.addHandler(ws);
    }
    server.on("/*", HTTP_GET, handlePublicFiles);
    server.begin();
}