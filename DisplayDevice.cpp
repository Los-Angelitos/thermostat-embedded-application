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
}

// Manejo de eventos
void DisplayDevice::on(Event event) {
}

// Manejo de comandos
void DisplayDevice::handle(Command command) {
}

// Mostrar mensaje
void DisplayDevice::displayMessage(const std::string& message) {
}

// Limpiar pantalla
void DisplayDevice::clearDisplay() {
}

// Posicionar cursor
void DisplayDevice::setCursor(int col, int row) {
}