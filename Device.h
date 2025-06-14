#ifndef DEVICE_H
#define DEVICE_H

/**
 * This file defines the Device class, which represents a device that can handle events and commands.
 * 
 * The Device class inherits from both EventHandler and CommandHandler, allowing it to respond to events and handle commands.
 * It provides pure virtual methods for handling events and commands, which must be implemented by derived classes.
 * 
 * Usage:
 * To create a custom device, derive from the Device class and implement the on() method to handle events and the handle() method to process commands.
 * The on() method will be called with an Event object when an event occurs, and the handle() method will be called with a Command object when a command is issued.
 * 
 * @author Arian Rodriguez
 * @date June 13, 2025
 * @version 1.0
 */

#include "EventHandler.h"
#include "CommandHandler.h"

class Device : public EventHandler, public CommandHandler {
public:
    virtual void on(Event event) override = 0;
    virtual void handle(Command command) override = 0;
    virtual ~Device() = default;
};

#endif // DEVICE_H