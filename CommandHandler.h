#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

/**
 * @file CommandHandler.h
 * @brief This file defines the Command and CommandHandler classes.
 * 
 * The Command class represents a command with a unique identifier.
 * The CommandHandler class is an abstract base class that defines an interface for handling commands.
 * The CommandHandler class requires derived classes to implement the handle() method to process commands.
 * The Command class includes an equality operator to compare commands based on their identifiers.
 * 
 * Usage:
 * To create a custom command handler, derive from the CommandHandler class and implement the handle() method.
 * The handle() method will be called with a Command object when a command is issued.
 * 
 * @author Arian Rodriguez
 * @date June 13, 2025
 * @version 1.0
 */

struct Command {
  int id;
  
  explicit Command(int commandId) : id(commandId) {}
  bool operator==(const Command& other) const {
    return id == other.id;
  }
};

class CommandHandler {
public:
  virtual void handle(Command command) = 0;
  virtual ~CommandHandler() = default;
};

#endif