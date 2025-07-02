#ifndef ACTUATOR_H
#include "CommandHandler.h"

/**
 * @file Actuator.h
 * @brief This file defines the Actuator class, which represents an actuator that can handle commands.
 * * The Actuator class inherits from CommandHandler and implements the handle method to process commands.
 * * The Actuator class can be associated with a GPIO pin and can delegate command handling to another CommandHandler.
 * * Usage:
 * To create an actuator, instantiate the Actuator class with a GPIO pin number and optionally a command handler.
 * The handle method will be called with a Command object when a command is issued.
 * 
 * @author Arian Rodriguez
 * @date June 13, 2025
 * @version 1.0
 */

class Actuator : public CommandHandler {
protected:
    int pin; ///< GPIO pin assigned to the actuator.
    CommandHandler* handler; ///< Optional handler to receive propagated commands.

public:
    Actuator(int pin, CommandHandler* commandHandler = nullptr);
    void handle(Command command) override;
    void setHandler(CommandHandler* commandHandler);
};

#endif // ACTUATOR_H