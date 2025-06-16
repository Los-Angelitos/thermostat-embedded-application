/**
 * @file ThermostatDevice.cpp
 * @brief This file implements the ThermostatDevice class, which represents a thermostat device that can handle temperature events and commands.
 * 
 * The ThermostatDevice class inherits from Device and implements the on() method to handle temperature events and the handle() method to process temperature commands.
 * It provides methods to set and get the current temperature, as well as to set a target temperature.
 * * Usage:
 * * To create a thermostat device, derive from the ThermostatDevice class and implement the on() method to handle temperature events and the handle() method to process temperature commands.
 * 
 * * @author Fabia Herrera
 * * @date June 14, 2025
 * * * @version 1.0
 * 
 */

#include "ThermostatDevice.h"
#include <Arduino.h>

ThermostatDevice::ThermostatDevice(const std::string& name, int initialTemperature)
    : name(name), currentTemperature(initialTemperature), targetTemperature(initialTemperature) {}

void ThermostatDevice::on(Event event) {
    // Handle temperature-related events
    if (event.id == 1) { // Example event ID for temperature change
        Serial.print("Event received: Temperature change to ");
        Serial.println(currentTemperature);
    } else {
        Serial.print("Unhandled event: ");
        Serial.println(event.id);
    }
}

void ThermostatDevice::handle(Command command) {
    // Handle temperature-related commands
    if (command.id == 1) { // Example command ID for setting target temperature
        Serial.print("Command received: Set target temperature to ");
        Serial.println(targetTemperature);
    } else {
        Serial.print("Unhandled command: ");
        Serial.println(command.id);
    }
}

void ThermostatDevice::setCurrentTemperature(int temperature) {
    currentTemperature = temperature;
    Serial.print("Current temperature set to: ");
    Serial.println(currentTemperature);
}

int ThermostatDevice::getCurrentTemperature() const {
    return currentTemperature;
}

void ThermostatDevice::setTargetTemperature(int temperature) {
    targetTemperature = temperature;
    Serial.print("Target temperature set to: ");
    Serial.println(targetTemperature);
}

int ThermostatDevice::getTargetTemperature() const {
    return targetTemperature;
}

std::string ThermostatDevice::getName() const {
    return name;
}