#define SERIAL_BAUDRATE 115200
#define ID_RELAY "pippo"
#define NAME "Pippo"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <fauxmoESP.h>

fauxmoESP fauxmo;
WiFiManager wifiManager;

char input;
boolean relayState = false;
const int relayPin = D1;

/**
 * @brief wifiSetup initialises the wifi manager.
 * If no connection found, it will setup as an access point with the name defined as NAME (above)
 */
void wifiSetup()
{
  Serial.print("Pippo: Wifi setup");

//  wifiManager.resetSettings();

  wifiManager.autoConnect(NAME);
}

/**
 * @brief fauxmoSetup sets up the Wemos as an alexa compatible device.
 * You can add more than one setting to it, but as we're only turning on 1 relay, addDevice is only called once.
 * By default, fauxmoESP creates it's own webserver on the defined port (TCP port must be 80 for "gen3" devices and set before callng enable())
 */
void fauxmoSetup()
{

  Serial.print("Pippo: Fauxmo setup");

  fauxmo.createServer(true);
  fauxmo.setPort(80);
  fauxmo.enable(true);

  fauxmo.addDevice(ID_RELAY);

  // This is where the magic happens to change the state of the device
  fauxmo.onSetState([](unsigned char device_id, const char *device_name, bool state, unsigned char value)
                    {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

    if (strcmp(device_name, ID_RELAY) == 0) {
      digitalWrite(relayPin, state ? HIGH : LOW);
    } });
}

/**
 * @brief All Arduino projects have two functions by default. Setup and Loop.
 * The setup function is typically called first and sets up the device for what it's going to forever loop over.
 * In this case the setup configures pin D1 on the board to be an output, sets up the wifi and then makes it an Alexa device (above)
 */
void setup()
{

  // Serial setup - This lets you debug/interact with the Wemos (you'll see in the loop below)
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  Serial.print("Pippo: Serial started");

  // PIN setup - Makes D1 and output (vs an input like a switch etc) and sets its initial value to 1/ON/HIGH (3.3v in this case)
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  // Setup wifi and fauxmo
  wifiSetup();
  fauxmoSetup();
}

/**
 * @brief The loop function is what the device will does for the rest of its life whilst running.
 * Technically its just a Polling function but you can interrupt it... but thats for another time.
 * This loop just checks if theres an update to fauxmo or if there has been any input.
 */
void loop()
{
  // Using the Serial "monitor", you can read the output of the Wemos as long as the Baudrate is the same (115200 in this case)
  // The code below lets you enter either a '1' or '0' to manually change the state of the relay.
  if (Serial.available())
  {

    input = Serial.read();

    if (input == '0')
    {
      fauxmo.setState(ID_RELAY, true, 0);
      digitalWrite(relayPin, LOW);
      Serial.print("Off");
    }

    if (input == '1')
    {
      fauxmo.setState(ID_RELAY, true, 255);
      digitalWrite(relayPin, HIGH);
      Serial.print("On");
    }
  }

  // Check fauxmo...
  fauxmo.handle();

  // This is more an Arduino/ESP thing. The memory on these devices is very low so you can occasionally free up some space to reduce memory leaks...
  static unsigned long last = millis();
  if (millis() - last > 5000)
  {
    last = millis();
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  }
}
