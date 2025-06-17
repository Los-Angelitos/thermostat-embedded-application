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

#define DEBOUNCE_DELAY_MS 8000 // 10 seconds debounce delay for HTTP request
#define LCD_UPDATE_INTERVAL_MS 1000 // 1 second update interval for LCD display

#define ENDPOINT_POST_TEMPERATURE "http://host.wokwi.internal:3000/api/v1/monitoring/thermostats"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define DEVICE_ID "TH-01"
#define API_KEY "thermostat-key"

ThermostatDevice thermostat("Living Room Thermostat", 22); 
LiquidCrystal_I2C lcd(0x27, 16, 2);

HTTPClient httpClient;
JsonDocument dataRecord;

#define CONTENT_TYPE_HEADER "Content-Type"
#define APPLICATION_JSON "application/json"

#define STATE true
#define EVENT_ID_READY 0

#define TEMPERATURE_DEFAULT 22

// signings for the methods
std::pair<bool, int> handleReadyEvent();

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

  dataRecord["device_id"] = DEVICE_ID;
  dataRecord["api_key"] = API_KEY;

  thermostat.setCurrentTemperature(TEMPERATURE_DEFAULT);
  thermostat.setTargetTemperature(TEMPERATURE_DEFAULT + 2);

  Event readyEvent(EVENT_ID_READY);
  thermostat.on(readyEvent);
}

void loop() {
    delay(DEBOUNCE_DELAY_MS);

 if(WiFi.status() == WL_CONNECTED) {
    // call the handleReadyEvent function to simulate the device being ready
    
    std::pair<bool, int> response = handleReadyEvent();
    if(!response.first) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Device off");
      return;
    }

    thermostat.setCurrentTemperature(response.second);

    Serial.println(response.first);
    Serial.println(response.second);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    lcd.print(thermostat.getCurrentTemperature());
    lcd.print("C");    
  }else {
    Serial.println("WiFi disconnected");
    lcd.clear();
  }

}

// function to know if the device is ready
std::pair<bool, int> handleReadyEvent() {
  Serial.println("Getting if the device is ready...");
  httpClient.begin(ENDPOINT_POST_TEMPERATURE);
  dataRecord["current_temperature"] = thermostat.getCurrentTemperature();

  String dataRecordResource;
  serializeJson(dataRecord, dataRecordResource);
  Serial.print("Sending JSON: ");
  Serial.println(dataRecordResource);

  httpClient.addHeader(CONTENT_TYPE_HEADER, APPLICATION_JSON);
  int httpCode = httpClient.POST(dataRecordResource);
  Serial.print("HTTP Response Code: ");
  Serial.println(httpCode);

  JsonDocument response;
  String responseResource;
  responseResource = httpClient.getString();
  Serial.print("Raw response: ");
  Serial.println(responseResource);
  deserializeJson(response, responseResource);
  serializeJsonPretty(response, Serial);
  Serial.println();

  std::pair<bool, int> varResponse;
  varResponse.first = response["state"].as<bool>();
  varResponse.second = response["current_temperature"].as<int>();

  httpClient.end();

  return varResponse;
}
