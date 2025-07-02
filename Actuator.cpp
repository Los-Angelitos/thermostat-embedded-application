/**
 * @file Actuator.cpp
 * 
 * This file implements the Actuator class, which represents an actuator that can handle commands.
 * The Actuator class inherits from CommandHandler and implements the handle method to process commands.
 * The Actuator class can be associated with a GPIO pin and can delegate command handling to another CommandHandler.
 * 
 * Usage:
 * To create an actuator, instantiate the Actuator class with a GPIO pin number and optionally a command handler.
 * The handle method will be called with a Command object when a command is issued.
 * 
 * @author Fabia Herrera
 * @date June 14, 2025
 * @version 1.0
 */

#include "Actuator.h"

Actuator::Actuator(int pin, CommandHandler* commandHandler)
    : pin(pin), handler(commandHandler) {}

void Actuator::handle(Command command) {
    if (handler != nullptr) {
        handler->handle(command);
    }
}

void Actuator::setHandler(CommandHandler* commandHandler) {
    handler = commandHandler;
}