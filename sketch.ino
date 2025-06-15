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
#include "ModestIoT.h"
#include "ThermostatDevice.h"

#include <HttpClient.h>

#define DEBOUNCE_DELAY_MS 5000 // 5 seconds debounce delay for HTTP request
#define LCD_UPDATE_INTERVAL_MS 1000 // 1 second update interval for LCD display

const char* ssid = "Wokwi-GUEST";
const char* password = "";

ThermostatDevice thermostat("Living Room Thermostat", 22); // Create a thermostat device with an initial temperature of 22 degrees
DisplayDevice display("Thermostat Display", 16, 2); // Create a display device with 16 columns and 2 rows

const char* serverUrl = "https://sweet-manager.free.beeceptor.com";
const bool state = true; // State of the thermostat (true for on, false for off)
const int EVENT_ID_READY = 0; // Event ID for ready state
HttpClient httpClient(); // Create an HTTP client to send requests to the server

// function to know if the device is ready
bool handleReadyEvent() {
    Serial.println("Device is ready. Sending initial temperature data to server...");

    // JSON payload mocked for the status device is ready
    String jsonPayload = "{\"ip_address\": \"192.168.1.5\", \"state\": " + String(state ? "true" : "false") + "}";

    // parse the state for know if the thermostat is on or off
    return state;
}

int currentTemperatureFromGuestPreference() {
    /*
    httpClient.setHeader("Content-Type", "application/json");
    httpClient.setHeader("Accept", "application/json");
    httpClient.get("/api/v1/thermostat/current-temperature");
    int currentTemperature = httpClient.getResponseCode();
    if (currentTemperature < 0) {
        Serial.println("Failed to retrieve current temperature from guest preference.");
        return -1; // Indicate failure
    }

    Serial.print("Current temperature from guest preference: ");
    Serial.println(currentTemperature);
    */

    return 26; // Mocked current temperature for demonstration purposes
}

void setup() {
    Serial.begin(115200); // Initialize serial communication for debugging
    Serial.println("Modest IoT Thermostat Device SweetManager");

    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println(" conectado!");
    
    // Set initial temperature
    thermostat.setCurrentTemperature(22);
    thermostat.setTargetTemperature(24); // Set target temperature to 24 degrees

    // Simulate an event to indicate the device is ready
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
            display.clearDisplay();
            display.setCursor(0, 0);
            display.displayMessage("Current Temp:");
            display.setCursor(0, 1);
            display.displayMessage(String(thermostat.getCurrentTemperature()).c_str());
            Serial.print("Current temperature set to: ");
            Serial.println(thermostat.getCurrentTemperature());
        } else {
            Serial.println("Failed to set current temperature from server data.");
        }
    }else {
        Serial.println("Device is not ready, skipping temperature data retrieval.");
    }

    delay(DEBOUNCE_DELAY_MS);
    
  }else {
    Serial.println("WiFi disconnected");
  }
}