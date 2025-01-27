#include <WiFi.h>
#include <ESPmDNS.h>

const char *ssid = "Network";
const char *password = "WifiPassword";

void wifiSetup(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("backdrop");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("backdrop"))
    {
        Serial.println("mDNS responder gestartet: backdrop.local");
    }
    else
    {
        Serial.println("mDNS start fehlgeschlagen");
    }
}
