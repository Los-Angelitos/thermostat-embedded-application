/**
 * @file DisplayDevice.cpp
 * @brief This file implements the DisplayDevice class, which represents a device that can display information on a screen.
 * 
 * The DisplayDevice class inherits from the Device class and provides methods to display information on a screen.
 * * Usage:
 * To create a display device, derive from the DisplayDevice class and implement the on() method to handle events and the handle() method to process commands.
 * * The on() method will be called with an Event object when an event occurs, and the handle() method will be called with a Command object when a command is issued.
 * * @author Fabia Herrera
 * @date June 14, 2025
 * @version 1.0
 */
#include "DisplayDevice.h"
#include <Arduino.h>

// Inicializa el constructor con parámetros del LCD
DisplayDevice::DisplayDevice(const std::string& name, int cols, int rows, int address)
    : lcd(address, cols, rows) {
    lcd.init();        // Inicializa el LCD
    lcd.backlight();   // Enciende la luz de fondo
}

// Manejo de eventos
void DisplayDevice::on(Event event) {
    if (event.id == 1) {
        Serial.print("Display event received: ");
        Serial.println(event.id);
    } else {
        Serial.print("Unhandled display event: ");
        Serial.println(event.id);
    }
}

// Manejo de comandos
void DisplayDevice::handle(Command command) {
    if (command.id == 1) {
        Serial.print("Display command received: ");
        Serial.println(command.id);
    } else {
        Serial.print("Unhandled display command: ");
        Serial.println(command.id);
    }
}

// Mostrar mensaje
void DisplayDevice::displayMessage(const std::string& message) {
    Serial.print("Displaying message: ");
    Serial.println(message.c_str());
    lcd.print(message.c_str());
}

// Limpiar pantalla
void DisplayDevice::clearDisplay() {
    Serial.println("Clearing display");
    lcd.clear();
}

// Posicionar cursor
void DisplayDevice::setCursor(int col, int row) {
    Serial.print("Setting cursor to column ");
    Serial.print(col);
    Serial.print(", row ");
    Serial.println(row);
    lcd.setCursor(col, row);
}