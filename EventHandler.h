#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

/**
 * @file EventHandler.h
 * @brief This file defines the Event and EventHandler classes.
 * 
 * The Event class represents an event with a unique identifier.
 * The EventHandler class is an abstract base class that defines an interface for handling events.
 * The EventHandler class requires derived classes to implement the on() method to handle events.
 * The Event class includes an equality operator to compare events based on their identifiers.
 * 
 * Usage:
 * To create a custom event handler, derive from the EventHandler class and implement the on() method.
 * The on() method will be called with an Event object when an event occurs.
 * 
 * @author Fabia Herrera
 * @date June 14, 2025
 * @version 1.0
 */

struct Event {
  int id;

  explicit Event(int eventId) : id(eventId) {}
  bool operator==(const Event& other) const {
    return id == other.id;
  }
};

class EventHandler {
public:
  virtual void on(Event event) = 0;
  virtual ~EventHandler() = default;
};

#endif