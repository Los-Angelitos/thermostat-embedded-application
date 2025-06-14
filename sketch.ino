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

#include "ModestIoT.h"
#include "ThermostatDevice.h"

#include <HttpClient.h>

#define DEBOUNCE_DELAY_MS 5000 // 5 seconds debounce delay for HTTP request
#define LCD_UPDATE_INTERVAL_MS 1000 // 1 second update interval for LCD display

ThermostatDevice thermostat("Living Room Thermostat", 22); // Create a thermostat device with an initial temperature of 22 degrees

const char* serverUrl = "https://sweet-manager.free.beeceptor.com/api/v1/monitoring/thermostats";
const bool state = true; // State of the thermostat (true for on, false for off)
HttpClient httpClient(serverUrl); // Create an HTTP client to send requests to the server

// function to know if the device is ready
bool handleReadyEvent() {
    Serial.println("Device is ready. Sending initial temperature data to server...");

    // JSON payload mocked for the status device is ready
    String jsonPayload = "{\"ip_address\": \"192.168.1.5\", \"state\": " + String(state ? "true" : "false") + "}";

    // parse the state for know if the thermostat is on or off
    return state;
}

void setup() {
    Serial.begin(115200); // Initialize serial communication for debugging
    Serial.println("Modest IoT Thermostat Device SweetManager");

    // Set initial temperature
    thermostat.setCurrentTemperature(22);
    thermostat.setTargetTemperature(24); // Set target temperature to 24 degrees

    // Simulate an event to indicate the device is ready
    Event readyEvent(0); // Event ID 0 for device ready
    thermostat.on(readyEvent);
}

void loop() {
    // call the handleReadyEvent function to simulate the device being ready
    if(handleReadyEvent()) {
        Serial.println("Device is ready, recovering the temperature data...");

        // Simulate getting the current temperature from the server
        int data = httpClient.get();
        if (data >= 0) {
            Serial.print("Current temperature from server: ");
            Serial.println(data);
            thermostat.setCurrentTemperature(data); // Update the thermostat with the current temperature
        } else {
            Serial.println("Failed to retrieve temperature data from server.");
        }
    }
}