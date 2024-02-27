#include <Arduino.h>
#include <WiFi.h>

void scanWifi();

// WIFI credentials
// (⊙_◎) = 4477882200As
const char *ssid = "(⊙_◎)";
const char *password = "4477882200As";

// LED configs
const int LIGHT_SENSOR_PIN = 36; // ESP32 pin GIOP36 (ADC0)
const int LED_PIN = 16;  // LED pin corresponds to GPIO16

// setting PWM properties
const int LED_PWD_FREQ = 5000;
const int LED_CHANNEL = 0;
const int RESOLUTION = 8;

// Scan wifi and list them in the console
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

// Connect the wifi to the given credentials
void initWiFi()
{
  WiFi.mode(WIFI_STA);
  scanWifi();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(100);
  }
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}

void setup() {
  Serial.begin(9600);
  initWiFi();
  ledcSetup(LED_CHANNEL, LED_PWD_FREQ, RESOLUTION); // configure LED PWM functionalities
  ledcAttachPin(LED_PIN, LED_CHANNEL); // attach the channel to the GPIO to be controlled
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  // Serial.write(analogValue);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few thresholds, qualitatively determined
  if (analogValue < 40) {
    Serial.println(" => Dark");
  } else if (analogValue < 800) {
    Serial.println(" => Dim");
  } else if (analogValue < 2000) {
    Serial.println(" => Light");
  } else if (analogValue < 3200) {
    Serial.println(" => Bright");
  } else {
    Serial.println(" => Very bright");
  }

  // changing the LED brightness with PWM
  int transformedValue = (analogValue * 255) / 4095;
  ledcWrite(LED_CHANNEL, transformedValue);   

  delay(30);
}
