/**
 * @file sketch.ino
 * @brief This is the main sketch file for the Modest IoT framework, demonstrating the use of the ThermostatDevice class.
 * * This sketch initializes a ThermostatDevice and simulates temperature events and commands.
 * * The sketch includes the necessary headers for the Modest IoT framework and sets up the device to handle temperature events and commands.
 * 
 * * Usage:
 * * To run this sketch, upload it to an Arduino board with the Modest IoT framework installed.
 * * * The sketch will initialize a ThermostatDevice and simulate temperature events and commands, printing the results to the Serial Monitor.
 * 
 * @author Arian Rodriguez
 * @date June 13, 2025
 * @version 1.0
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "ModestIoT.h"
#include "ThermostatDevice.h"

#define DEBOUNCE_DELAY_MS 30000 // 10 seconds debounce delay for HTTP request
#define LCD_UPDATE_INTERVAL_MS 1000 // 1 second update interval for LCD display
#define ENDPOINT_GET_THERMOSTAT_READY "https://sweet-manager.free.beeceptor.com/api/v1/monitoring/thermostats?ip_address=192.168.1.5"
#define ENDPOINT_GET_TEMPERATURE_GUEST "https://sweet-manager.free.beeceptor.com/api/v1/monitoring/temperature?ip_address=192.168.1.5"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

ThermostatDevice thermostat("Living Room Thermostat", 22); 
DisplayDevice display("Thermostat Display", 16, 2); 
LiquidCrystal_I2C lcd(0x27, 16, 2);

HTTPClient httpClient;

#define CONTENT_TYPE_HEADER "Content-Type"
#define APPLICATION_JSON "application/json"

#define STATE true
#define EVENT_ID_READY 0

#define TEMPERATURE_DEFAULT 22

// signings for the methods
bool handleReadyEvent();
int currentTemperatureFromGuestPreference();

void setup() {
  Serial.begin(115200);
  Serial.println("Modest IoT Thermostat Device SweetManager");
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print("Connected!");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected: ");
  Serial.println(WiFi.localIP());

  thermostat.setCurrentTemperature(TEMPERATURE_DEFAULT);
  thermostat.setTargetTemperature(TEMPERATURE_DEFAULT + 2);

  //Simulate an event to indicate the device is ready

  Event readyEvent(EVENT_ID_READY);
  thermostat.on(readyEvent);
}

void loop() {
 if(WiFi.status() == WL_CONNECTED) {
    // call the handleReadyEvent function to simulate the device being ready
    if(handleReadyEvent()) {
        Serial.println("Device is ready, recovering the temperature data...");

        // Simulate getting the current temperature from the server
        int data = currentTemperatureFromGuestPreference();
        if (data >= 0) {
            thermostat.setCurrentTemperature(data); // Set the current temperature from the server data
            // Update the display with the current temperature

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Temperature= ");
            lcd.print(data);
            delay(1000);
           
            Serial.print("Current temperature set to: ");
            Serial.println(thermostat.getCurrentTemperature());
        } else {
            Serial.println("Failed to set current temperature from server data.");
        }
    }else {
        Serial.println("Device is not ready, skipping temperature data retrieval.");
        lcd.clear();
    }

    delay(DEBOUNCE_DELAY_MS);
    
  }else {
    Serial.println("WiFi disconnected");
    lcd.clear();
  }
}

// function to know if the device is ready
bool handleReadyEvent() {
  Serial.println("Getting if the device is ready...");
  bool state = false;

  httpClient.begin(ENDPOINT_GET_THERMOSTAT_READY);
  httpClient.addHeader(CONTENT_TYPE_HEADER, APPLICATION_JSON);

  int httpResponseCode = httpClient.GET();
  Serial.print("Response code: ");
  Serial.println(httpResponseCode);

  if (httpResponseCode == 200) {
    String responseResource = httpClient.getString();
    
    StaticJsonDocument<256> response; // Usa tamaño adecuado según el JSON
    DeserializationError error = deserializeJson(response, responseResource);

    if (!error) {
      serializeJsonPretty(response, Serial); // Ver para depuración

      // Leer "state" directamente del objeto JSON
      if (response.containsKey("state")) {
        state = response["state"].as<bool>();
        Serial.print("Extracted state: ");
        Serial.println(state ? "true" : "false");
      } else {
        Serial.println("Key 'state' not found in JSON.");
      }
    } else {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
    }
  } else {
    Serial.println("HTTP request failed.");
  }

  httpClient.end(); // Liberar recursos
  return state;
}


int currentTemperatureFromGuestPreference() {
  Serial.println("Getting the current temperature of the guest...");
  int temperature = TEMPERATURE_DEFAULT;

  httpClient.begin(ENDPOINT_GET_TEMPERATURE_GUEST);
  httpClient.addHeader(CONTENT_TYPE_HEADER, APPLICATION_JSON);

  int httpResponseCode = httpClient.GET();
  Serial.print("Response code: ");
  Serial.println(httpResponseCode);

  if (httpResponseCode == 200) {
    String responseResource = httpClient.getString();

    StaticJsonDocument<256> response;
    DeserializationError error = deserializeJson(response, responseResource);

    if (!error) {
      serializeJsonPretty(response, Serial);

      if (response.containsKey("temperature")) {
        temperature = response["temperature"].as<int>();
        Serial.print("Extracted temperature: ");
        Serial.println(temperature);
      } else {
        Serial.println("Key 'temperature' not found.");
      }
    } else {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
    }
  } else {
    Serial.println("HTTP request failed.");
  }

  httpClient.end();
  return temperature;
}
