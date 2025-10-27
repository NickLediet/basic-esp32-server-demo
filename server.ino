#include <Arduino.h>


#ifdef ESP8266 // This example is compatible with both, ATMega and ESP8266
   #include <ESP8266WiFi.h>
#else
   #include <SPI.h> //! \todo Temporary see fix: https://github.com/platformio/platformio/issues/48
   #include <WiFi.h>
#endif

const char* SSID = "";
const char* PASSWORD = "";
const int PING_DELAY = 500;
const int PORT = 3000;
const int LED_GPIO = 17;
bool ledState = false;

WiFiServer server(PORT);

void bindWiFi() {
  Serial.println("\nConnection to Wifi...");
  WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(PING_DELAY);
  }
  Serial.println("\nConnected!");
}

void configureGPIO() {
  pinMode(LED_GPIO, OUTPUT);
}

void blinkLED() {
  Serial.println("Turning on LED");
  digitalWrite(LED_GPIO, HIGH);
  delay(2000);
  Serial.println("Turning off LED");
  digitalWrite(LED_GPIO, LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  configureGPIO();
  blinkLED();
  Serial.println("\nInitializing....");

  bindWiFi();
  
  server.begin();
  Serial.println("\sIP Address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();
  
  if(client) {
    if(client.connected()) {
      if(!ledState) {
        ledState = true;
        digitalWrite(LED_GPIO, HIGH);
      } else {
        ledState = false;
        digitalWrite(LED_GPIO, LOW);
      }
      // Serial.println("Client request recieved!");
      // // Serial.println("Connected to client!");
      // client.write("HTTP/1.1 200 OK\r\n");
      // client.write("Content-Type: text/html\r\n");
      // // client.write("Connection: close\r\n");
      // client.write("\r\n");  // End of headers

      // client.write("<!DOCTYPE html>\r\n");
      // client.write("<html>\r\n");
      // client.write("<head><title>Hello</title></head>\r\n");
      // client.write("<body>\r\n");
      // client.write("<h1>Hello, World!</h1>\r\n");
      // client.write("</body>\r\n");
      // client.write("</html>\r\n");
      // // Serial.println("</html>");
    }
    client.flush();
    delay(10);
    client.stop();
  }
}