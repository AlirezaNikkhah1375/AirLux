#include <Arduino.h>
#include <WiFi.h>

void scanWifi();

const char *ssid = "WIFI_SSID_REQUIRED";
const char *password = "WIFI_PASSWORD_REQUIRED";

void scanWifi()
{
  WiFi.disconnect();
  delay(100);
  Serial.println("Wifi Scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Wifi Scan done");
  if (n == 0)
  {
    Serial.println("No networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}

void initWiFi()
{
  WiFi.mode(WIFI_STA);
  scanWifi();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}

void setup()
{
  Serial.begin(9600);
  initWiFi();
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("hello from test");
  delay(20000);
}